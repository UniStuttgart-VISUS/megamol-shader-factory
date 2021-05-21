/*
 * Copyright (C) 2020-2021 University of Stuttgart (VISUS).
 * All rights reserved.
 */
#include "msf/LineTranslator.h"

#include <algorithm>
#include <regex>

msf::LineTranslator::LineTranslator() : next_id_(10000) {}

std::string msf::LineTranslator::cleanupShader(const std::string& shader_source) {
    std::vector<std::string> file_list;

    const std::regex find_lines("(?:^|\n)#line [0-9]+ \"(.*)\"");
    std::sregex_iterator it(shader_source.begin(), shader_source.end(), find_lines);
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

    for (auto const& file : file_list) {
        file_ids_.emplace_back(std::make_pair(next_id_, file));
        next_id_++;
    }

    // Replace file string by id
    std::string clean_source = shader_source;
    for (auto const& file_id : file_ids_) {
        const std::regex replace_lines("(^|\n)#line ([0-9]+) \"" + file_id.second + "\"");
        clean_source = std::regex_replace(clean_source, replace_lines, "$1#line $2 " + std::to_string(file_id.first));
    }

    // remove GL_GOOGLE_include_directive extension
    clean_source =
        std::regex_replace(clean_source, std::regex("(^|\n)#extension[ ]*GL_GOOGLE_include_directive(.*)\n"), "\n");

    return clean_source;
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
