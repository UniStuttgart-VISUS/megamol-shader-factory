/*
 * Copyright (C) 2020-2023 University of Stuttgart (VISUS).
 * All rights reserved.
 */
#pragma once

#include <filesystem>
#include <fstream>
#include <regex>
#include <sstream>
#include <string>

namespace msf {

static std::string readFileToString(std::filesystem::path const& file_path, bool normalize_new_line = true) {
    std::ifstream file(file_path);
    std::stringstream buffer;
    buffer << file.rdbuf();
    if (!normalize_new_line) {
        return buffer.str();
    }
    // First replace all "\r\n" by "\n", then in a second pass all stand-alone "\r" by "\n".
    static const auto ln_win = std::regex("\r\n");
    static const auto ln_mac = std::regex("\r");
    auto str = buffer.str();
    str = std::regex_replace(str, ln_win, "\n");
    str = std::regex_replace(str, ln_mac, "\n");
    return str;
}

} // namespace msf
