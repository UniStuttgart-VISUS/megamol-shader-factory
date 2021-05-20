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

#include "glslang/Public/ShaderLang.h"

#include "msf/utils.h"

namespace megamol::shaderfactory {

class includer final : public glslang::TShader::Includer {
public:
    explicit includer(std::vector<std::filesystem::path> shader_include_paths);

    IncludeResult* includeSystem(const char* header_name, const char* includer_name, size_t inclusion_depth) override;

    void releaseInclude(IncludeResult* inc_res) override;

    ~includer() override = default;

private:
    std::vector<std::filesystem::path> shader_include_paths_;
};

} // end namespace megamol::shaderfactory
