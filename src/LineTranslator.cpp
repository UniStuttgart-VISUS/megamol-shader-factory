/*
 * Copyright (C) 2020-2021 University of Stuttgart (VISUS).
 * All rights reserved.
 */
#include "msf/LineTranslator.h"

#include <regex>
#include <sstream>

msf::LineTranslator::LineTranslator() : next_id_(10000) {}

std::string msf::LineTranslator::cleanupShader(const std::string& shader_source) {
    // The shader factory outputs #line annotations in the following form:
    //   #line 123 "source.glsl"
    // GLSL standard only allows two ints as params for #line. Therefore, we
    // replace the string with an int and store the int to filename mapping.
    //
    // The allowed range of the second in param depends on the driver:
    // NVIDIA: int32_t
    // AMD: int16_t
    // Intel: uint16_t
    // Therefore, the max int id we should use is 32767 (max of short).
    // Start by 10000 to constantly use 5 char numbers for stable regex replacement later.

    const std::regex line_pattern("^#line ([0-9]+) \"(.*)\".*");
    const std::regex google_include_pattern("^#extension[ ]*GL_GOOGLE_include_directive.*");
    std::smatch match;

    std::stringstream clean_source;
    std::istringstream stream(shader_source);
    std::string line;
    while (std::getline(stream, line)) {
        // Remove windows line ending
        if (!line.empty() && line.back() == '\r') {
            line.pop_back();
        }

        if (std::regex_match(line, match, line_pattern)) {
            id_file_map_[next_id_] = match[2].str();
            clean_source << "#line " << match[1].str() << " " << next_id_ << '\n';
            next_id_++;
        } else if (std::regex_match(line, google_include_pattern)) {
            // remove this line
            continue;
        } else {
            clean_source << line << '\n';
        }
    }

    return clean_source.str();
}

std::string msf::LineTranslator::translateErrorLog(std::string const& message) const {
    // NVIDIA:  10000(123) : error[...]
    // AMD:     ERROR: 10000:123: [...]
    // Intel:   ERROR: 10000:123: [...]

    std::regex msg_pattern("([0-9]{5})([:|\\(][0-9]+[:|\\)])");
    std::smatch match;
    std::stringstream result;
    std::istringstream stream(message);
    std::string line;
    while (std::getline(stream, line)) {
        if (std::regex_search(line, match, msg_pattern)) {
            auto const id = std::stoi(match[1].str());
            auto const it = id_file_map_.find(id);
            if (it != id_file_map_.end()) {
                result << match.prefix() << it->second << match[2].str() << match.suffix() << '\n';
                continue;
            }
        }
        result << line << '\n';
    }

    return result.str();
}
