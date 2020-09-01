#pragma once

#include <filesystem>
#include <fstream>
#include <mutex>

#include "shaderc/shaderc.hpp"

#include "glad/glad.h"

namespace megamol::shaderfactory {

class compiler {
public:
    compiler() {}

    compiler(compiler const&) = delete;
    compiler& operator=(compiler const&) = delete;

    compiler(compiler&&) = delete;
    compiler& operator=(compiler&&) = delete;

    ~compiler() {}

    [[nodiscard]] std::string preprocess(
        std::filesystem::path const& shader_source_path, shaderc::CompileOptions const& options) const;

private:
    static std::string read_shader_source(std::filesystem::path const& shader_source_path) {
        auto const size = std::filesystem::file_size(shader_source_path);
        std::ifstream file(shader_source_path);

        std::string content;
        content.resize(size);
        file.read(content.data(), size);

        file.close();

        return content;
    }

    shaderc::Compiler compiler_;

    std::mutex compiler_lock_;
};

shaderc_shader_kind parse_type_string(std::string const& shader_type) {
    if (shader_type == ".vert") {
        return shaderc_vertex_shader;
    }

    if (shader_type == ".tesc") {
        return shaderc_tess_control_shader;
    }

    if (shader_type == ".tese") {
        return shaderc_tess_evaluation_shader;
    }

    if (shader_type == ".geom") {
        return shaderc_geometry_shader;
    }

    if (shader_type == ".frag") {
        return shaderc_fragment_shader;
    }

    if (shader_type == ".comp") {
        return shaderc_compute_shader;
    }

    return shaderc_glsl_infer_from_source;
}

GLenum parse_type_string(shaderc_shader_kind const& shader_type) {
    if (shader_type == shaderc_vertex_shader) {
        return GL_VERTEX_SHADER;
    }

    if (shader_type == shaderc_tess_control_shader) {
        return GL_TESS_CONTROL_SHADER;
    }

    if (shader_type == shaderc_tess_evaluation_shader) {
        return GL_TESS_EVALUATION_SHADER;
    }

    if (shader_type == shaderc_geometry_shader) {
        return GL_GEOMETRY_SHADER;
    }

    if (shader_type == shaderc_fragment_shader) {
        return GL_FRAGMENT_SHADER;
    }

    if (shader_type == shaderc_compute_shader) {
        return GL_COMPUTE_SHADER;
    }

    return 0;
}

shaderc_shader_kind get_shader_type_sc(std::filesystem::path const& shader_source_path) {
    auto const shader_type_string = shader_source_path.stem().extension().string();

    return parse_type_string(shader_type_string);
}

GLenum get_shader_type_ogl(std::filesystem::path const& shader_source_path) {
    return parse_type_string(get_shader_type_sc(shader_source_path));
}

} // end namespace megamol::shaderfactory
