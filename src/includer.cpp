/*
 * includer.cpp
 *
 * Copyright (C) 2020-2021 by Universitaet Stuttgart (VISUS). Alle Rechte vorbehalten.
 */
#include "msf/includer.h"
#include "msf/utils.h"

#include <fstream>


megamol::shaderfactory::includer::includer(std::vector<std::filesystem::path> const& shader_include_paths)
    : shader_include_paths_(shader_include_paths) {}


glslang::TShader::Includer::IncludeResult* read_include(std::filesystem::path const& search_path) {
    auto fsize = std::filesystem::file_size(search_path);
    std::ifstream file(search_path);
    auto shader_source = new char[fsize];
    file.read(shader_source, fsize);
    return new glslang::TShader::Includer::IncludeResult(std::filesystem::canonical(search_path).string(), shader_source, fsize, nullptr);
}


glslang::TShader::Includer::IncludeResult* megamol::shaderfactory::includer::includeSystem(
    const char* header_name, const char* includer_name, size_t inclusion_depth) {
    for (auto const& el : shader_include_paths_) {
        auto search_path = el;
        search_path /= header_name;
        if (std::filesystem::exists(search_path)) {
            return read_include(search_path);
        }
    }
    return nullptr;
}


void megamol::shaderfactory::includer::releaseInclude(glslang::TShader::Includer::IncludeResult* data) {
    if (data != nullptr) {
        safe_delete_array(data->headerData);
        safe_delete(data->userData);
    }
}
