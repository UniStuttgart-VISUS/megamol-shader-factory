/*
 * compiler_options.h
 *
 * Copyright (C) 2020 by Universitaet Stuttgart (VISUS). Alle Rechte vorbehalten.
 */
#pragma once

#include <filesystem>
#include <vector>

#include "shaderc/shaderc.hpp"

#include "msf/includer.h"
#include "msf/includer_dispatch.h"

#include "glad/glad.h"

namespace megamol::shaderfactory {

inline void default_compiler_options(shaderc::CompileOptions& options) {
    options.SetOptimizationLevel(shaderc_optimization_level_performance);
    options.SetSourceLanguage(shaderc_source_language_glsl);
    options.SetTargetEnvironment(shaderc_target_env_opengl_compat, shaderc_env_version_opengl_4_5);
}


class compiler_options;


void add_vendor_definition(compiler_options& options);


/**
 * Utility for defining shaderc compiler options.
 */
class compiler_options {
public:
    compiler_options() {
        default_compiler_options(options_);
        add_vendor_definition(*this);
    }

    void add_definition(std::string const& name) { options_.AddMacroDefinition(name); }

    void add_definition(std::string const& name, std::string const& value) { options_.AddMacroDefinition(name, value); }

    /**
     * Set include paths. Overrides previously set paths.
     */
    void set_include_paths(std::vector<std::filesystem::path> const& paths) {
        shader_paths_ = paths;

        if (paths.size() == 0) return;
        if (paths.size() == 1) {
            options_.SetIncluder(std::make_unique<includer>(paths[0]));
            return;
        }

        auto dispatcher = std::make_unique<includer_dispatch>();

        for (auto const& el : paths) {
            dispatcher->set_include_path(el);
        }

        options_.SetIncluder(std::move(dispatcher));
    }

    operator shaderc::CompileOptions const &() const { return options_; }

    std::vector<std::filesystem::path> const& get_shader_paths() const { return shader_paths_; }

private:
    shaderc::CompileOptions options_;

    std::vector<std::filesystem::path> shader_paths_;
}; // end class compiler_options


inline void add_vendor_definition(compiler_options& options) {
    std::basic_string<GLubyte> const tmp(glGetString(GL_VENDOR));
    std::string vendor_str;
    vendor_str.resize(tmp.size());
    std::transform(tmp.cbegin(), tmp.cend(), vendor_str.begin(), [](GLubyte chr) { return std::tolower(chr); });

    if (vendor_str.find("ati") != std::string::npos || vendor_str.find("amd") != std::string::npos) {
        options.add_definition("__AMD__");
    }

    if (vendor_str.find("nvidia") != std::string::npos) {
        options.add_definition("__NVIDIA__");
    }

    if (vendor_str.find("intel") != std::string::npos) {
        options.add_definition("__INTEL__");
    }
}

} // end namespace megamol::shaderfactory
