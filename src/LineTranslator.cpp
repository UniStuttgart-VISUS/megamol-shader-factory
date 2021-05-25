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
    // GLSL standard only allows allows two ints as params for #line. Therefore,
    // we replace the string with an int and store the int to filename mapping.
    //
    // The allowed range of the second in param depends on the driver:
    // NVIDIA: int32_t
    // AMD: int16_t
    // Intel: uint16_t
    // Therefore, the max int id we should use is 32767 (max of short).
    // Just start by 10000 to constantly use 5 char numbers for stable regex replacement later.

    const std::regex line_pattern("^#line ([0-9]+) \"(.*)\".*");
    const std::regex google_include_pattern("^#extension[ ]*GL_GOOGLE_include_directive.*");
    std::smatch match;

    std::istringstream stream(shader_source);
    std::stringstream clean_source;
    std::string line;
    while (std::getline(stream, line)) {
        // Remove windows line ending
        if (!line.empty() && line.back() == '\r') {
            line.pop_back();
        }

        if (std::regex_match(line, match, line_pattern)) {
            clean_source << "#line " << match[1] << " " << filenameToId(match[2]) << '\n';
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
    std::smatch sm;
    std::stringstream result;
    std::istringstream stream(message);
    for (std::string line; std::getline(stream, line);) {
        if (std::regex_search(line, sm, msg_pattern)) {
            auto const id = std::stoi(sm[1].str());
            auto const it = file_id_map_.find(id);
            if (it != file_id_map_.end()) {
                result << sm.prefix() << it->second << sm[2].str() << sm.suffix() << '\n';
                continue;
            }
        }
        result << line << '\n';
    }

    return result.str();
}

int msf::LineTranslator::filenameToId(const std::string& filename) {
    int new_id = next_id_;
    next_id_++;
    file_id_map_[new_id] = filename;
    return new_id;
}
