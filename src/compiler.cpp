/*
 * compiler.cpp
 *
 * Copyright (C) 2020-2021 by Universitaet Stuttgart (VISUS). Alle Rechte vorbehalten.
 */
#include "msf/compiler.h"

#include "msf/includer.h"

#include <algorithm>
#include <sstream>
#include <string>
#include <tuple>

/*
 * default resource limits for glslang compiler
 * Adapted from: https://github.com/google/shaderc/blob/main/libshaderc_util/src/resources.cc
 * License: Apache 2.0
 */
const TBuiltInResource default_resource_limits = {
    /*.maxLights = */ 8,        // From OpenGL 3.0 table 6.46.
    /*.maxClipPlanes = */ 6,    // From OpenGL 3.0 table 6.46.
    /*.maxTextureUnits = */ 2,  // From OpenGL 3.0 table 6.50.
    /*.maxTextureCoords = */ 8, // From OpenGL 3.0 table 6.50.
    /*.maxVertexAttribs = */ 16,
    /*.maxVertexUniformComponents = */ 1024,
    /*.maxVaryingFloats = */ 60, // From OpenGLES 3.1 table 6.44.
    /*.maxVertexTextureImageUnits = */ 16,
    /*.maxCombinedTextureImageUnits = */ 80,
    /*.maxTextureImageUnits = */ 16,
    /*.maxFragmentUniformComponents = */ 1024,

    /*.maxDrawBuffers = */ 8,

    /*.maxVertexUniformVectors = */ 256,
    /*.maxVaryingVectors = */ 15,
    /*.maxFragmentUniformVectors = */ 256,
    /*.maxVertexOutputVectors = */ 16,  // maxVertexOutputComponents / 4
    /*.maxFragmentInputVectors = */ 32, // maxFragmentInputComponents / 4
    /*.minProgramTexelOffset = */ -8,
    /*.maxProgramTexelOffset = */ 7,
    /*.maxClipDistances = */ 8,
    /*.maxComputeWorkGroupCountX = */ 65535,
    /*.maxComputeWorkGroupCountY = */ 65535,
    /*.maxComputeWorkGroupCountZ = */ 65535,
    /*.maxComputeWorkGroupSizeX = */ 1024,
    /*.maxComputeWorkGroupSizeY = */ 1024,
    /*.maxComputeWorkGroupSizeZ = */ 64,
    /*.maxComputeUniformComponents = */ 1024,
    /*.maxComputeTextureImageUnits = */ 16,
    /*.maxComputeImageUniforms = */ 8,
    /*.maxComputeAtomicCounters = */ 8,
    /*.maxComputeAtomicCounterBuffers = */ 8,
    /*.maxVaryingComponents = */ 60,
    /*.maxVertexOutputComponents = */ 64,
    /*.maxGeometryInputComponents = */ 64,
    /*.maxGeometryOutputComponents = */ 128,
    /*.maxFragmentInputComponents = */ 128,
    /*.maxImageUnits = */ 8,
    /*.maxCombinedImageUnitsAndFragmentOutputs = */ 8, // ?
    /*.maxCombinedShaderOutputResources = */ 8,
    /*.maxImageSamples = */ 0,
    /*.maxVertexImageUniforms = */ 0,
    /*.maxTessControlImageUniforms = */ 0,
    /*.maxTessEvaluationImageUniforms = */ 0,
    /*.maxGeometryImageUniforms = */ 0,
    /*.maxFragmentImageUniforms = */ 8,
    /*.maxCombinedImageUniforms = */ 8,
    /*.maxGeometryTextureImageUnits = */ 16,
    /*.maxGeometryOutputVertices = */ 256,
    /*.maxGeometryTotalOutputComponents = */ 1024,
    /*.maxGeometryUniformComponents = */ 1024,
    /*.maxGeometryVaryingComponents = */ 60, // Does not seem to be defined
                                             // anywhere, set equal to
                                             // maxVaryingComponents.
    /*.maxTessControlInputComponents = */ 128,
    /*.maxTessControlOutputComponents = */ 128,
    /*.maxTessControlTextureImageUnits = */ 16,
    /*.maxTessControlUniformComponents = */ 1024,
    /*.maxTessControlTotalOutputComponents = */ 4096,
    /*.maxTessEvaluationInputComponents = */ 128,
    /*.maxTessEvaluationOutputComponents = */ 128,
    /*.maxTessEvaluationTextureImageUnits = */ 16,
    /*.maxTessEvaluationUniformComponents = */ 1024,
    /*.maxTessPatchComponents = */ 120,
    /*.maxPatchVertices = */ 32,
    /*.maxTessGenLevel = */ 64,
    /*.maxViewports = */ 16,
    /*.maxVertexAtomicCounters = */ 0,
    /*.maxTessControlAtomicCounters = */ 0,
    /*.maxTessEvaluationAtomicCounters = */ 0,
    /*.maxGeometryAtomicCounters = */ 0,
    /*.maxFragmentAtomicCounters = */ 8,
    /*.maxCombinedAtomicCounters = */ 8,
    /*.maxAtomicCounterBindings = */ 1,
    /*.maxVertexAtomicCounterBuffers = */ 0,

    /*.maxTessControlAtomicCounterBuffers = */ 0,
    /*.maxTessEvaluationAtomicCounterBuffers = */ 0,
    /*.maxGeometryAtomicCounterBuffers = */ 0,

    /*.maxFragmentAtomicCounterBuffers = */ 1,
    /*.maxCombinedAtomicCounterBuffers = */ 1,
    /*.maxAtomicCounterBufferSize = */ 32,
    /*.maxTransformFeedbackBuffers = */ 4,
    /*.maxTransformFeedbackInterleavedComponents = */ 64,
    /*.maxCullDistances = */ 8,
    /*.maxCombinedClipAndCullDistances = */ 8,
    /*.maxSamples = */ 4,
    /* .maxMeshOutputVerticesNV = */ 256,
    /* .maxMeshOutputPrimitivesNV = */ 512,
    /* .maxMeshWorkGroupSizeX_NV = */ 32,
    /* .maxMeshWorkGroupSizeY_NV = */ 1,
    /* .maxMeshWorkGroupSizeZ_NV = */ 1,
    /* .maxTaskWorkGroupSizeX_NV = */ 32,
    /* .maxTaskWorkGroupSizeY_NV = */ 1,
    /* .maxTaskWorkGroupSizeZ_NV = */ 1,
    /* .maxMeshViewCountNV = */ 4,
    /* .maxDualSourceDrawBuffersEXT = */ 1,

    /*.limits = */
    {
        /*.nonInductiveForLoops = */ 1,
        /*.whileLoops = */ 1,
        /*.doWhileLoops = */ 1,
        /*.generalUniformIndexing = */ 1,
        /*.generalAttributeMatrixVectorIndexing = */ 1,
        /*.generalVaryingIndexing = */ 1,
        /*.generalSamplerIndexing = */ 1,
        /*.generalVariableIndexing = */ 1,
        /*.generalConstantMatrixVectorIndexing = */ 1,
    }};

/*
 * Adapted from : https://github.com/google/shaderc/blob/main/libshaderc_util/src/compiler.cc
 * License : Apache 2.0
 */
std::tuple<bool, int, EProfile> find_and_parse_version_string(std::string const& shader_source) {
    auto version_pos = shader_source.find("#version");
    if (version_pos == std::string::npos) {
        return std::make_tuple(false, 0, ENoProfile);
    }
    auto version_string = shader_source.substr(version_pos + std::strlen("#version"));
    version_string = version_string.substr(0, version_string.find_first_of('\n'));
    version_string.erase(std::remove(version_string.begin(), version_string.end(), ' '), version_string.end());
    int version = 0;
    std::string profile_name;
    std::istringstream(version_string) >> version >> profile_name;

    EProfile profile = ENoProfile;

    if (profile_name == glslang::ProfileName(ECoreProfile)) {
        profile = ECoreProfile;
    }
    if (profile_name == glslang::ProfileName(ECompatibilityProfile)) {
        profile = ECompatibilityProfile;
    }

    return std::make_tuple(true, version, profile);
}


std::string megamol::shaderfactory::compiler::preprocess(
    std::filesystem::path const& shader_source_path, compiler_options const& options) const {
    std::filesystem::path final_shader_source_path;
    if (std::filesystem::exists(shader_source_path)) {
        final_shader_source_path = shader_source_path;
    } else if (shader_source_path.is_relative()) {
        bool found_path = false;
        for (auto const& el : options.get_shader_paths()) {
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

    glslang::TShader shader(EShLangVertex);

    // auto const shader_type = get_shader_type_sc(final_shader_source_path);

    auto const shader_source = read_shader_source(final_shader_source_path);

    auto const shader_source_ptr = shader_source.data();
    auto const shader_source_length = static_cast<int>(shader_source.size());
    auto const shader_source_name = std::filesystem::canonical(final_shader_source_path).string();
    auto const shader_source_name_ptr = shader_source_name.c_str();

    shader.setStringsWithLengthsAndNames(&shader_source_ptr, &shader_source_length, &shader_source_name_ptr, 1);

    auto preamble = options.get_preamble();

    shader.setPreamble(preamble.c_str());

    shader.setEnvClient(glslang::EShClientOpenGL, glslang::EShTargetOpenGL_450);

    bool succes_version_string = false;
    int version = 0;
    EProfile profile = ENoProfile;
    std::tie(succes_version_string, version, profile) = find_and_parse_version_string(shader_source);
    if (!succes_version_string) {
        return std::string();
    }

    auto inc = options.get_includer();
    std::string output;
    auto const success =
        shader.preprocess(&default_resource_limits, version, profile, true, false, EShMsgDefault, &output, inc);

    if (!success) {
        throw std::runtime_error(std::string("Error preprocessing shader:\n") + shader.getInfoLog());
    }

    auto version_pos = output.find("#version");
    auto version_end = output.find_first_of('\n', version_pos) + 1;
    auto version_string = output.substr(version_pos, version_end - version_pos);
    output.erase(version_pos, version_end - version_pos);
    output.insert(0, version_string);

    return output;
}
