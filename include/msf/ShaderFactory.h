/*
 * Copyright (C) 2020-2023 University of Stuttgart (VISUS).
 * All rights reserved.
 */
#pragma once

#include <filesystem>

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
    static inline int glslangInitReferenceCounter_ = 0;
};

} // namespace msf
