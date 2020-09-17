/*
 * includer_dispatch.h
 *
 * Copyright (C) 2020 by Universitaet Stuttgart (VISUS). Alle Rechte vorbehalten.
 */
#include "msf/includer_dispatch.h"


void megamol::shaderfactory::includer_dispatch::set_include_path(std::filesystem::path const& path) {
    includer_assoc_[path.string()] = std::make_unique<includer>(path);
}


shaderc_include_result* megamol::shaderfactory::includer_dispatch::GetInclude(
    const char* requested_source, shaderc_include_type type, const char* requesting_source, size_t include_depth) {
    for (auto const& el : includer_assoc_) {
        auto res = el.second->GetInclude(requested_source, type, requesting_source, include_depth);
        if (res->content != nullptr) {
            set_user_data(res->user_data, el.first);
            return res;
        }
    }
    return new shaderc_include_result{0};
}


void megamol::shaderfactory::includer_dispatch::ReleaseInclude(shaderc_include_result* data) {
    if (data->user_data != nullptr) {
        auto const& path = reinterpret_cast<user_data_t*>(data->user_data)->path;
        auto fit = includer_assoc_.find(path.string());
        if (fit != includer_assoc_.end()) {
            fit->second->ReleaseInclude(data);
            return;
        }
    }

    default_delete_include_result(data);
}
