/*
 * includer.h
 *
 * Copyright (C) 2020-2021 by Universitaet Stuttgart (VISUS). Alle Rechte vorbehalten.
 */
#pragma once

#include <filesystem>
#include <fstream>
#include <string>
#include <vector>

#include <glslang/Public/ShaderLang.h>

#include "msf/utils.h"

namespace msf {

class Includer final : public glslang::TShader::Includer {
public:
    explicit Includer(std::vector<std::filesystem::path> shader_include_paths);

    ~Includer() override = default;

    IncludeResult* includeSystem(const char* header_name, const char* includer_name, size_t inclusion_depth) override;

    void releaseInclude(IncludeResult* inc_res) override;

private:
    std::vector<std::filesystem::path> shader_include_paths_;
};

} // namespace msf
