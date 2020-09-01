#pragma once

#include <filesystem>
#include <vector>

#include "shaderc/shaderc.hpp"

#include "msf/includer.h"
#include "msf/includer_dispatch.h"

namespace megamol::shaderfactory {

inline void default_compiler_options(shaderc::CompileOptions& options) {
    options.SetOptimizationLevel(shaderc_optimization_level_performance);
    options.SetSourceLanguage(shaderc_source_language_glsl);
    options.SetTargetEnvironment(shaderc_target_env_opengl_compat, shaderc_env_version_opengl_4_5);
}

/**
 * Utility for defining shaderc compiler options.
 */
class compiler_options {
public:
    compiler_options() { default_compiler_options(options_); }

    void add_definition(std::string const& name) { options_.AddMacroDefinition(name); }

    void add_definition(std::string const& name, std::string const& value) { options_.AddMacroDefinition(name, value); }

    /**
     * Set include paths. Overrides previously set paths.
     */
    void set_include_paths(std::vector<std::filesystem::path> const& paths) {
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

private:
    shaderc::CompileOptions options_;
}; // end class compiler_options

} // end namespace megamol::shaderfactory
