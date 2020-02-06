#pragma once

#include <filesystem>
#include <fstream>
#include <mutex>

#include "shaderc/shaderc.hpp"

namespace megamol::shaderfactory {

class compiler {
public:
    compiler() {}

    compiler(compiler const&) = delete;
    compiler& operator=(compiler const&) = delete;

    compiler(compiler&&) = delete;
    compiler& operator=(compiler&&) = delete;

    ~compiler() {}

private:
    static shaderc_shader_kind parse_type_string(std::string const& shader_type) {
        if (shader_type == ".vert") {
            return shaderc_vertex_shader;
        }

        if (shader_type == ".tesc") {
            return shaderc_tess_control_shader;
        }

        if (shader_type == ".tese") {
            return shaderc_tess_control_shader;
        }

        if (shader_type == ".geom") {
            return shaderc_tess_control_shader;
        }

        if (shader_type == ".frag") {
            return shaderc_tess_control_shader;
        }

        if (shader_type == ".comp") {
            return shaderc_tess_control_shader;
        }

        return shaderc_glsl_infer_from_source;
    }

    static std::string read_shader_source(std::filesystem::path const& shader_source_path) {
        auto const size = std::filesystem::file_size(shader_source_path);
        std::ifstream file(shader_source_path);

        std::string content;
        content.resize(size);
        file.read(content.data(), size);

        file.close();

        return content;
    }

    [[nodiscard]] std::string preprocess(std::filesystem::path const& shader_source_path) const;

    shaderc::Compiler compiler_;

    std::mutex compiler_lock_;
};

} // end namespace megamol::shaderfactory
