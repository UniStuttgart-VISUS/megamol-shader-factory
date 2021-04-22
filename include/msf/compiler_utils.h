/*
 * compiler_utils.h
 *
 * Copyright (C) 2020-2021 by Universitaet Stuttgart (VISUS). Alle Rechte vorbehalten.
 */
#pragma once

#include <filesystem>
#include <string>

#include "glslang/Public/ShaderLang.h"

#include "glad/glad.h"

namespace megamol::shaderfactory {

inline std::string get_shader_type_string(std::filesystem::path const& shader_source_path) {
    std::string ext_type = std::tolower(shader_source_path.extension().string());
    if (ext_type == ".glsl") {
        return std::tolower(shader_source_path.stem().extension().string());
    }
    return ext_type;
}


inline EShLanguage parse_type_string_glslang(std::string const& shader_type) {
    if (shader_type == ".vert") {
        return EShLangVertex;
    }

    if (shader_type == ".tesc") {
        return EShLangTessControl;
    }

    if (shader_type == ".tese") {
        return EShLangTessEvaluation;
    }

    if (shader_type == ".geom") {
        return EShLangGeometry;
    }

    if (shader_type == ".frag") {
        return EShLangFragment;
    }

    if (shader_type == ".comp") {
        return EShLangCompute;
    }

    return EShLangCount;
}


inline EShLanguage get_shader_type_glslang(std::filesystem::path const& shader_source_path) {
    auto const shader_type_string = get_shader_type_string(shader_source_path);
    return parse_type_string_glslang(shader_type_string);
}


inline GLenum parse_type_string_ogl(std::string const& shader_type) {
    if (shader_type == ".vert") {
        return GL_VERTEX_SHADER;
    }

    if (shader_type == ".tesc") {
        return GL_TESS_CONTROL_SHADER;
    }

    if (shader_type == ".tese") {
        return GL_TESS_EVALUATION_SHADER;
    }

    if (shader_type == ".geom") {
        return GL_GEOMETRY_SHADER;
    }

    if (shader_type == ".frag") {
        return GL_FRAGMENT_SHADER;
    }

    if (shader_type == ".comp") {
        return GL_COMPUTE_SHADER;
    }

    return 0;
}


inline GLenum get_shader_type_ogl(std::filesystem::path const& shader_source_path) {
    auto const shader_type_string = get_shader_type_string(shader_source_path);
    return parse_type_string_ogl(shader_type_string);
}

} // namespace megamol::shaderfactory
