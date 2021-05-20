/*
 * compiler.h
 *
 * Copyright (C) 2020-2021 by Universitaet Stuttgart (VISUS). Alle Rechte vorbehalten.
 */
#pragma once

#include <filesystem>
#include <fstream>

#include "ShaderFactoryOptions.h"

namespace msf {

class ShaderFactory {
public:
    ShaderFactory();
    ~ShaderFactory();

    ShaderFactory(ShaderFactory const&) = delete;
    ShaderFactory(ShaderFactory&&) = delete;
    ShaderFactory& operator=(ShaderFactory const&) = delete;
    ShaderFactory& operator=(ShaderFactory&&) = delete;

    [[nodiscard]] std::string preprocess(
        std::filesystem::path const& shader_source_path, ShaderFactoryOptions const& options) const;

private:
    static std::string readShaderSource(std::filesystem::path const& shader_source_path) {
        auto const size = std::filesystem::file_size(shader_source_path);
        std::ifstream file(shader_source_path);

        std::string content;
        content.resize(size);
        file.read(content.data(), size);

        file.close();

        return content;
    }
};

} // namespace msf
