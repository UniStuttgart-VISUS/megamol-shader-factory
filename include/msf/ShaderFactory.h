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
};

} // namespace msf
