/*
 * Copyright (C) 2020-2021 University of Stuttgart (VISUS).
 * All rights reserved.
 */
#pragma once

#include <filesystem>
#include <string>
#include <utility>
#include <vector>

namespace msf {

struct macro {
    explicit macro(std::string name) : name_(std::move(name)) {}

    macro(std::string name, std::string val) : name_(std::move(name)), val_(std::move(val)) {}

    std::string name_;
    std::string val_;
};

/**
 * Utility for defining shader factory options.
 */
class ShaderFactoryOptions {
public:
    explicit ShaderFactoryOptions(std::vector<std::filesystem::path> include_paths)
            : include_paths_(std::move(include_paths)) {}

    void addDefinition(std::string const& name) {
        macros_.emplace_back(name);
    }

    void addDefinition(std::string const& name, std::string const& value) {
        macros_.emplace_back(name, value);
    }

    /**
     * Set include paths. Overrides previously set paths.
     */
    void setIncludePaths(std::vector<std::filesystem::path> const& paths) {
        include_paths_ = paths;
    }

    [[nodiscard]] std::vector<std::filesystem::path> const& getIncludePaths() const {
        return include_paths_;
    }

    [[nodiscard]] std::vector<macro> const& getMacros() const {
        return macros_;
    }

private:
    std::vector<macro> macros_;

    std::vector<std::filesystem::path> include_paths_;
}; // end class compiler_options

} // namespace msf
