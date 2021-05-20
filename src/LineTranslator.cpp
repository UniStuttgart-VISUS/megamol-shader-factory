/*
 * Copyright (C) 2020-2021 University of Stuttgart (VISUS).
 * All rights reserved.
 */
#include "msf/LineTranslator.h"

#include <algorithm>
#include <regex>

msf::LineTranslator::LineTranslator(std::string const& shader_source) {

    std::vector<std::string> file_list;

    std::regex line_pattern("(?:^|\n)#line [0-9]+ \"(.*)\"");
    std::sregex_iterator it(shader_source.begin(), shader_source.end(), line_pattern);
    auto it_end = std::sregex_iterator();

    while (it != it_end) {
        file_list.emplace_back((*it)[1]);
        it++;
    }

    std::sort(file_list.begin(), file_list.end());
    file_list.erase(std::unique(file_list.begin(), file_list.end()), file_list.end());

    // Replace source strings by numbers.
    // Max number should be 32767 (max of short).
    // Size of source file id depends on driver:
    // NVIDIA: int32_t
    // AMD: int16_t
    // Intel: uint16_t

    // Just start by 10000 to constantly use 5 char numbers for stable regex replacement later.
    int id = 10000;
    for (auto const& file : file_list) {
        file_ids_.emplace_back(std::make_pair(id, file));
        id++;
    }

    // Replace file string by id
    clean_source_ = shader_source;
    for (auto const& file_id : file_ids_) {
        std::regex line_pattern("(^|\n)#line ([0-9]+) \"" + file_id.second + "\"");
        clean_source_ = std::regex_replace(clean_source_, line_pattern, "$1#line $2 " + std::to_string(file_id.first));
    }

    // remove GL_GOOGLE_include_directive extension
    clean_source_ =
        std::regex_replace(clean_source_, std::regex("(^|\n)#extension[ ]*GL_GOOGLE_include_directive(.*)\n"), "\n");
}

std::string msf::LineTranslator::translateErrorLog(std::string const& message) const {
    // NVIDIA:  10000(123) : error[...]
    // AMD:     ERROR: 10000:123: [...]
    // Intel:   ERROR: 10000:123: [...]

    std::string result = message;
    for (auto const& file_id : file_ids_) {
        result = std::regex_replace(
            result, std::regex(std::to_string(file_id.first) + "(:|\\()([0-9]+)(:|\\))"), file_id.second + "$1$2$3");
    }
    return result;
}
