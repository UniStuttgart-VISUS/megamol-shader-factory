/*
 * Copyright (C) 2020-2021 University of Stuttgart (VISUS).
 * All rights reserved.
 */
#include "msf/ShaderFactory.h"

#include <algorithm>
#include <regex>
#include <sstream>
#include <string>
#include <tuple>

#include <ResourceLimits.h>
#include <glslang/Public/ShaderLang.h>

#include "Includer.h"
#include "Utils.h"
#include "msf/ShaderFactoryUtils.h"

namespace {

std::tuple<bool, int, EProfile> find_and_parse_version_string(std::string const& shader_source) {
    // Find first '#version' at beginning of a line (ignoring white spaces)
    std::regex regex("(^|\n)\\s*#version\\s*(.*)");
    std::smatch match;
    if (std::regex_search(shader_source, match, regex)) {
        int version = 0;
        std::string profile_name;
        std::istringstream(match[2].str()) >> version >> profile_name;

        EProfile profile = ENoProfile;

        if (profile_name == glslang::ProfileName(ECoreProfile)) {
            profile = ECoreProfile;
        } else if (profile_name == glslang::ProfileName(ECompatibilityProfile)) {
            profile = ECompatibilityProfile;
        } else if (profile_name == glslang::ProfileName(EEsProfile)) {
            profile = EEsProfile;
        }

        return std::make_tuple(true, version, profile);
    }

    return std::make_tuple(false, 0, ENoProfile);
}

EShLanguage get_shader_type(std::filesystem::path const& file_path) {
    auto const shader_ext = msf::getShaderExtensionString(file_path);
    if (shader_ext == ".vert") {
        return EShLanguage::EShLangVertex;
    }
    if (shader_ext == ".tesc") {
        return EShLanguage::EShLangTessControl;
    }
    if (shader_ext == ".tese") {
        return EShLanguage::EShLangTessEvaluation;
    }
    if (shader_ext == ".geom") {
        return EShLanguage::EShLangGeometry;
    }
    if (shader_ext == ".frag") {
        return EShLanguage::EShLangFragment;
    }
    if (shader_ext == ".comp") {
        return EShLanguage::EShLangCompute;
    }
    if (shader_ext == ".mesh") {
        return EShLanguage::EShLangMeshNV;
    }
    if (shader_ext == ".task") {
        return EShLanguage::EShLangTaskNV;
    }
    return EShLanguage::EShLangVertex;
}
} // namespace

msf::ShaderFactory::ShaderFactory() {
    if (glslangInitReferenceCounter_ <= 0) {
        glslang::InitializeProcess();
    }
    ++glslangInitReferenceCounter_;
}

msf::ShaderFactory::~ShaderFactory() {
    --glslangInitReferenceCounter_;
    if (glslangInitReferenceCounter_ <= 0) {
        glslang::FinalizeProcess();
        glslangInitReferenceCounter_ = 0;
    }
}

std::string msf::ShaderFactory::preprocess(
    std::filesystem::path const& shader_source_path, ShaderFactoryOptions const& options) const {
    std::filesystem::path final_shader_source_path;
    if (std::filesystem::exists(shader_source_path)) {
        final_shader_source_path = shader_source_path;
    } else if (shader_source_path.is_relative()) {
        bool found_path = false;
        for (auto const& el : options.getIncludePaths()) {
            auto search_path = el / shader_source_path;
            if (std::filesystem::exists(search_path)) {
                if (found_path) {
                    return std::string();
                } else {
                    found_path = true;
                    final_shader_source_path = search_path;
                }
            }
        }
    } else {
        return std::string();
    }

    glslang::TShader shader(get_shader_type(final_shader_source_path));

    auto const shader_source = readFileToString(final_shader_source_path);

    auto const shader_source_ptr = shader_source.data();
    auto const shader_source_length = static_cast<int>(shader_source.size());
    auto const shader_source_name = std::filesystem::canonical(final_shader_source_path).string();
    auto const shader_source_name_ptr = shader_source_name.c_str();

    shader.setStringsWithLengthsAndNames(&shader_source_ptr, &shader_source_length, &shader_source_name_ptr, 1);

    std::string preamble;
    preamble += "#extension GL_GOOGLE_include_directive : enable\n";
    for (auto const& macro : options.getMacros()) {
        if (!macro.name_.empty()) {
            preamble += "#define " + macro.name_;
            if (!macro.val_.empty()) {
                preamble += " " + macro.val_;
            }
            preamble += "\n";
        }
    }
    // #line must be last in preamble. Don't use a different line number than 1 or glslang will mess up lines!
    preamble += "#line 1 \"" + shader_source_name + "\"\n";

    shader.setPreamble(preamble.c_str());

    shader.setEnvClient(glslang::EShClientOpenGL, glslang::EShTargetOpenGL_450);

    bool succes_version_string = false;
    int version = 0;
    EProfile profile = ENoProfile;
    std::tie(succes_version_string, version, profile) = find_and_parse_version_string(shader_source);
    if (!succes_version_string) {
        throw std::runtime_error("Error preprocessing shader: missing #version");
    }

    Includer includer(options.getIncludePaths());
    std::string output;
    auto const success = shader.preprocess(
        &glslang::DefaultTBuiltInResource, version, profile, true, false, EShMsgDefault, &output, includer);

    if (!success) {
        throw std::runtime_error(std::string("Error preprocessing shader:\n") + shader.getInfoLog());
    }

    // make sure version is first line
    auto version_pos = output.find("#version");
    auto version_end = output.find_first_of('\n', version_pos);
    auto version_string = output.substr(version_pos, version_end - version_pos);
    output.erase(version_pos, version_end - version_pos); // keep '\n'
    output.insert(0, version_string + "\n");

    return output;
}
