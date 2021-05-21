/*
 * Copyright (C) 2020-2021 University of Stuttgart (VISUS).
 * All rights reserved.
 */
#pragma once

#include <string>
#include <unordered_map>

namespace msf {

class LineTranslator {
public:
    LineTranslator();
    ~LineTranslator() = default;

    std::string cleanupShader(const std::string& shader_source);

    [[nodiscard]] std::string translateErrorLog(std::string const& message) const;

private:
    int filenameToId(std::string const& filename);

    int next_id_;
    std::unordered_map<std::string, int> file_id_map_;
};

} // namespace msf
