/*
 * Copyright (C) 2020-2023 University of Stuttgart (VISUS).
 * All rights reserved.
 */
#include "msf/ShaderFactoryOptionsOpenGL.h"

#include <algorithm>

#define MSF_GL3W_IMPL
#include "gl/msf_opengl_loader.h"

void msf::ShaderFactoryOptionsOpenGL::addVendorDefinition() {
    static bool opengl_init = false;
    if (!opengl_init) {
        if (msf_gl3wInit() != 0) {
            throw std::runtime_error("Failed to initialize OpenGL loader!");
        }
        opengl_init = true;
    }

    std::string vendor = reinterpret_cast<const char*>(glGetString(GL_VENDOR));
    std::transform(vendor.begin(), vendor.end(), vendor.begin(), [](unsigned char c) { return std::tolower(c); });

    if (vendor.find("nvidia") != std::string::npos) {
        addDefinition("__NVIDIA__");
        return;
    }

    if (vendor.find("intel") != std::string::npos) {
        addDefinition("__INTEL__");
        return;
    }

    if (vendor.find("ati") != std::string::npos || vendor.find("amd") != std::string::npos) {
        addDefinition("__AMD__");
        return;
    }
}
