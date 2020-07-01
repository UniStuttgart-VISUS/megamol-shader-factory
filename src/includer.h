#pragma once

#include <filesystem>
#include <fstream>
#include <string>
#include <vector>

#include "shaderc/shaderc.hpp"

namespace megamol::shaderfactory {

class includer final : public shaderc::CompileOptions::IncluderInterface {
public:
    includer(std::filesystem::path const& shader_include_path);

    // Handles shaderc_include_resolver_fn callbacks.
    shaderc_include_result* GetInclude(const char* requested_source, shaderc_include_type type,
        const char* requesting_source, size_t include_depth) override;

    // Handles shaderc_include_result_release_fn callbacks.
    void ReleaseInclude(shaderc_include_result* data) override;

    virtual ~includer() = default;

private:
    std::filesystem::path shader_include_path_;
};

} // end namespace megamol::shaderfactory
