/*
 * compiler_options.cpp
 *
 * Copyright (C) 2020-2021 by Universitaet Stuttgart (VISUS). Alle Rechte vorbehalten.
 */
#include "msf/compiler_options.h"

#include "glad/glad.h"

void megamol::shaderfactory::compiler_options::add_vendor_definition() {
    std::basic_string<GLubyte> const tmp(glGetString(GL_VENDOR));
    std::string vendor_str;
    vendor_str.resize(tmp.size());
    std::transform(tmp.cbegin(), tmp.cend(), vendor_str.begin(), [](GLubyte chr) { return std::tolower(chr); });

    if (vendor_str.find("ati") != std::string::npos || vendor_str.find("amd") != std::string::npos) {
        add_definition("__AMD__");
    }

    if (vendor_str.find("nvidia") != std::string::npos) {
        add_definition("__NVIDIA__");
    }

    if (vendor_str.find("intel") != std::string::npos) {
        add_definition("__INTEL__");
    }
}
