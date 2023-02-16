/*
 * Copyright (C) 2020-2023 University of Stuttgart (VISUS).
 * All rights reserved.
 */
#pragma once

#include <algorithm>

#if defined(MSF_OPENGL_INCLUDE_GLAD)
#include <glad/glad.h>
#elif defined(MSF_OPENGL_INCLUDE_GLAD2)
#include <glad/gl.h>
#elif defined(MSF_OPENGL_INCLUDE_GL3W)
#include <GL/gl3w.h>
#elif defined(MSF_OPENGL_INCLUDE_GLEW)
#include <GL/glew.h>
#endif

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
    void addVendorDefinition() {
        std::basic_string<GLubyte> const tmp(glGetString(GL_VENDOR));
        std::string vendor_str;
        vendor_str.resize(tmp.size());
        std::transform(tmp.cbegin(), tmp.cend(), vendor_str.begin(), [](GLubyte chr) { return std::tolower(chr); });

        if (vendor_str.find("nvidia") != std::string::npos) {
            addDefinition("__NVIDIA__");
            return;
        }

        if (vendor_str.find("intel") != std::string::npos) {
            addDefinition("__INTEL__");
            return;
        }

        if (vendor_str.find("ati") != std::string::npos || vendor_str.find("amd") != std::string::npos) {
            addDefinition("__AMD__");
            return;
        }
    }
};

} // namespace msf
