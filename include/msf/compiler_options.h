/*
 * compiler_options.h
 *
 * Copyright (C) 2020-2021 by Universitaet Stuttgart (VISUS). Alle Rechte vorbehalten.
 */
#pragma once

#include <filesystem>
#include <utility>
#include <vector>

#include "glslang/Public/ShaderLang.h"

#include "msf/includer.h"

namespace megamol::shaderfactory {

struct macro {
    explicit macro(std::string name) : name_(std::move(name)) {}

    macro(std::string name, std::string val) : name_(std::move(name)), val_(std::move(val)) {}

    std::string name_;
    std::string val_;
};


/**
 * Utility for defining shaderc compiler options.
 */
class compiler_options {
public:
    explicit compiler_options(std::vector<std::filesystem::path> const& paths)
            : includer_(includer(paths)), paths_(paths) {
        add_vendor_definition();
    }

    compiler_options(std::vector<std::filesystem::path> const& paths, std::string const& vendor)
            : includer_(includer(paths)), paths_(paths) {
        add_definition(vendor);
    }

    void add_definition(std::string const& name) {
        macros_.emplace_back(name);
    }

    void add_definition(std::string const& name, std::string const& value) {
        macros_.emplace_back(name, value);
    }

    /**
     * Set include paths. Overrides previously set paths.
     */
    void set_include_paths(std::vector<std::filesystem::path> const& paths) {
        includer_ = includer(paths);
        paths_ = paths;
    }

    std::vector<std::filesystem::path> const& get_shader_paths() const {
        return paths_;
    }

    std::string get_preamble() const {
        std::string preamble;
        preamble += "#extension GL_GOOGLE_include_directive : enable\n";
        for (auto const& macro : macros_) {
            if (!macro.name_.empty()) {
                preamble += "#define " + macro.name_;
                if (!macro.val_.empty()) {
                    preamble += " " + macro.val_;
                }
                preamble += "\n";
            }
        }
        return preamble;
    }

    includer get_includer() const {
        return includer_;
    }

private:
    void add_vendor_definition();

    includer includer_;

    std::vector<macro> macros_;

    std::vector<std::filesystem::path> paths_;
}; // end class compiler_options


} // end namespace megamol::shaderfactory
