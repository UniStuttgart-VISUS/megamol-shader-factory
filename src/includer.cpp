#include "includer.h"
#include "utils.h"

#include <fstream>


megamol::shaderfactory::includer::includer(std::filesystem::path const& shader_include_path)
    : shader_include_path_(shader_include_path) {}


shaderc_include_result* megamol::shaderfactory::includer::GetInclude(
    const char* requested_source, shaderc_include_type type, const char* requesting_source, size_t include_depth) {
    auto const requested = std::filesystem::path(requested_source);
    auto const current_shader_path = std::filesystem::path(requesting_source);

    auto current_shader_base = current_shader_path;
    current_shader_base.remove_filename();

    auto search_name = requested.filename();
    auto search_path = current_shader_base.append(search_name.c_str());

    auto res = new shaderc_include_result{0};

    if (std::filesystem::exists(search_path)) {
        auto fsize = std::filesystem::file_size(search_path);
        std::ifstream file(search_path);
        auto shader_source = new char[fsize];
        file.read(shader_source, fsize);
        res->content = shader_source;
        res->content_length = fsize;
        file.close();
        auto sp_str = search_path.string();
        auto req_path = new char[sp_str.size()];
        std::copy(sp_str.cbegin(), sp_str.cend(), req_path);
        res->source_name = req_path;
        res->source_name_length = sp_str.size();
        return res;
    }

    search_path = shader_include_path_.append(search_name.c_str());
    if (std::filesystem::exists(search_path)) {
        auto fsize = std::filesystem::file_size(search_path);
        std::ifstream file(search_path);
        auto shader_source = new char[fsize];
        file.read(shader_source, fsize);
        res->content = shader_source;
        res->content_length = fsize;
        file.close();
        auto sp_str = search_path.string();
        auto req_path = new char[sp_str.size()];
        std::copy(sp_str.cbegin(), sp_str.cend(), req_path);
        res->source_name = req_path;
        res->source_name_length = sp_str.size();
        return res;
    }

    return res;
}


void megamol::shaderfactory::includer::ReleaseInclude(shaderc_include_result* data) {
    default_delete_include_result(data);
}
