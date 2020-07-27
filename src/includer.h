#pragma once

#include <filesystem>
#include <fstream>
#include <string>
#include <vector>

#include "shaderc/shaderc.hpp"

#include "utils.h"

namespace megamol::shaderfactory {

inline void default_delete_include_result(shaderc_include_result* data) {
    safe_delete_array(data->content);
    safe_delete_array(data->source_name);
    safe_delete(data->user_data);
}

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
