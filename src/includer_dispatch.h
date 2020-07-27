#pragma once

#include <filesystem>
#include <memory>
#include <string>
#include <unordered_map>

#include "shaderc/shaderc.hpp"

#include "includer.h"

namespace megamol::shaderfactory {

class includer_dispatch final : public shaderc::CompileOptions::IncluderInterface {
public:
    void set_include_path(std::filesystem::path const& path);

    // Handles shaderc_include_resolver_fn callbacks.
    shaderc_include_result* GetInclude(const char* requested_source, shaderc_include_type type,
        const char* requesting_source, size_t include_depth) override;

    // Handles shaderc_include_result_release_fn callbacks.
    void ReleaseInclude(shaderc_include_result* data) override;

private:
    struct user_data {
        std::filesystem::path path;
    };
    using user_data_t = user_data;

    void set_user_data(void*& user_data, std::filesystem::path const& path) {
        user_data = new user_data_t;
        reinterpret_cast<user_data_t*>(user_data)->path = path;
    }

    std::unordered_map<std::string, std::unique_ptr<includer>> includer_assoc_;
}; // end class includer_dispatch

} // end namespace megamol::shaderfactory
