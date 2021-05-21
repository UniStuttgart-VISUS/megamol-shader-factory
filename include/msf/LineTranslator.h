/*
 * Copyright (C) 2020-2021 University of Stuttgart (VISUS).
 * All rights reserved.
 */
#pragma once

#include <string>
#include <utility>
#include <vector>

namespace msf {

class LineTranslator {
public:
    LineTranslator();
    ~LineTranslator() = default;

    std::string cleanupShader(const std::string& shader_source);

    [[nodiscard]] std::string translateErrorLog(std::string const& message) const;

private:
    int next_id_;
    std::vector<std::pair<int, std::string>> file_ids_;
};

} // namespace msf
