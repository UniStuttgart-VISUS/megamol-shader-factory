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
    explicit LineTranslator(std::string const& shader_source);
    ~LineTranslator() = default;

    [[nodiscard]] std::string const& getCleanShader() const {
        return clean_source_;
    }

    std::string translateErrorLog(std::string const& message);

private:
    std::string clean_source_;
    std::vector<std::pair<int, std::string>> file_ids_;
};

} // namespace msf
