#include "includer.h"
#include "utils.h"


shaderc_include_result* megamol::shaderfactory::includer::GetInclude(
    const char* requested_source, shaderc_include_type type, const char* requesting_source, size_t include_depth) {
    auto const source_name = std::filesystem::path(requested_source);
    auto const current_shader_path = std::filesystem::path(requesting_source);

    auto current_shader_base = current_shader_path;
    current_shader_base.remove_filename();

    auto search_path = current_shader_base;
    search_path.append(source_name.begin(), source_name.end());

    if (std::filesystem::exists(search_path)) {
    }
}


void megamol::shaderfactory::includer::ReleaseInclude(shaderc_include_result* data) {
    safe_delete_array(data->content);
    safe_delete_array(data->source_name);
}
