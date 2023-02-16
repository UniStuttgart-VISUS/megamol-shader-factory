/*
 * Copyright (C) 2020-2023 University of Stuttgart (VISUS).
 * All rights reserved.
 */
#pragma once

#include <algorithm>
#include <filesystem>
#include <string>

namespace {
// from: https://en.cppreference.com/w/cpp/string/byte/tolower
std::string str_tolower(std::string s) {
    std::transform(s.begin(), s.end(), s.begin(), [](unsigned char c) { return std::tolower(c); });
    return s;
}
} // namespace

namespace msf {

// Stay compatible with OpenGL, hardcode values to not depend on any OpenGL include
enum class ShaderType : unsigned int {
    Vertex = 0x8B31,         // GL_VERTEX_SHADER
    TessControl = 0x8E88,    // GL_TESS_CONTROL_SHADER
    TessEvaluation = 0x8E87, // GL_TESS_EVALUATION_SHADER
    Geometry = 0x8DD9,       // GL_GEOMETRY_SHADER
    Fragment = 0x8B30,       // GL_FRAGMENT_SHADER
    Compute = 0x91B9,        // GL_COMPUTE_SHADER
    Mesh = 0x9559,           // GL_MESH_SHADER_NV
    Task = 0x955A,           // GL_TASK_SHADER_NV
    None = 0x0
};

static inline std::string getShaderExtensionString(std::filesystem::path const& file_path) {
    std::string ext_type = str_tolower(file_path.extension().string());
    if (ext_type == ".glsl") {
        return str_tolower(file_path.stem().extension().string());
    }
    return ext_type;
}

static inline ShaderType getShaderType(std::filesystem::path const& file_path) {
    auto shader_ext = getShaderExtensionString(file_path);
    if (shader_ext == ".vert") {
        return ShaderType::Vertex;
    }
    if (shader_ext == ".tesc") {
        return ShaderType::TessControl;
    }
    if (shader_ext == ".tese") {
        return ShaderType::TessEvaluation;
    }
    if (shader_ext == ".geom") {
        return ShaderType::Geometry;
    }
    if (shader_ext == ".frag") {
        return ShaderType::Fragment;
    }
    if (shader_ext == ".comp") {
        return ShaderType::Compute;
    }
    if (shader_ext == ".mesh") {
        return ShaderType::Mesh;
    }
    if (shader_ext == ".task") {
        return ShaderType::Task;
    }
    return ShaderType::None;
}

// compatible to GLenum
static inline unsigned int getShaderTypeInt(std::filesystem::path const& file_path) {
    return static_cast<std::underlying_type_t<ShaderType>>(getShaderType(file_path));
}

} // namespace msf
