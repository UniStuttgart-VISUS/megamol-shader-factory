/*
 * includer.cpp
 *
 * Copyright (C) 2020-2021 by Universitaet Stuttgart (VISUS). Alle Rechte vorbehalten.
 */
#include "Includer.h"

#include <fstream>
#include <utility>

#include "Utils.h"

namespace {

glslang::TShader::Includer::IncludeResult* read_include(std::filesystem::path const& search_path) {
    std::string* data = new std::string{msf::readFileToString(search_path)};
    return new glslang::TShader::Includer::IncludeResult(
        std::filesystem::canonical(search_path).string(), data->c_str(), data->size(), data);
}
} // namespace

msf::Includer::Includer(std::vector<std::filesystem::path> shader_include_paths)
        : shader_include_paths_(std::move(shader_include_paths)) {}


glslang::TShader::Includer::IncludeResult* msf::Includer::includeSystem(
    const char* header_name, const char* includer_name, size_t inclusion_depth) {
    for (auto const& el : shader_include_paths_) {
        auto search_path = el / header_name;
        if (std::filesystem::exists(search_path)) {
            return read_include(search_path);
        }
    }

    // lookup relative to file containing the include
    auto search_path = std::filesystem::path(includer_name).parent_path() / header_name;
    if (std::filesystem::exists(search_path)) {
        return read_include(search_path);
    }

    return nullptr;
}


void msf::Includer::releaseInclude(glslang::TShader::Includer::IncludeResult* result) {
    if (result != nullptr) {
        std::string* data = static_cast<std::string*>(result->userData);
        delete data;
        delete result;
    }
}
