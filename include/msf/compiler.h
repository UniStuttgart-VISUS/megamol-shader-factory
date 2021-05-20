/*
 * compiler.h
 *
 * Copyright (C) 2020-2021 by Universitaet Stuttgart (VISUS). Alle Rechte vorbehalten.
 */
#pragma once

#include <filesystem>
#include <fstream>

#include "msf/compiler_options.h"

namespace megamol::shaderfactory {

class compiler {
public:
    compiler();
    ~compiler();

    compiler(compiler const&) = delete;
    compiler& operator=(compiler const&) = delete;

    compiler(compiler&&) = delete;
    compiler& operator=(compiler&&) = delete;

    [[nodiscard]] std::string preprocess(
        std::filesystem::path const& shader_source_path, compiler_options const& options) const;

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
};

} // end namespace megamol::shaderfactory
