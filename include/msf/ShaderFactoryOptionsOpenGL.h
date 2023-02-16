/*
 * Copyright (C) 2020-2023 University of Stuttgart (VISUS).
 * All rights reserved.
 */
#pragma once

#include "ShaderFactoryOptions.h"

namespace msf {

class ShaderFactoryOptionsOpenGL : public ShaderFactoryOptions {
public:
    explicit ShaderFactoryOptionsOpenGL(std::vector<std::filesystem::path> include_paths)
            : ShaderFactoryOptions(std::move(include_paths)) {
        addVendorDefinition();
    }

    ShaderFactoryOptionsOpenGL(std::vector<std::filesystem::path> include_paths, std::string const& vendor)
            : ShaderFactoryOptions(std::move(include_paths)) {
        addDefinition(vendor);
    }

private:
    void addVendorDefinition();
};

} // namespace msf
