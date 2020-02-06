#pragma once

#include <filesystem>
#include <fstream>
#include <string>
#include <vector>

// #include "glslang/Public/ShaderLang.h"

namespace megamol {
namespace shaderfactory {

//class includer final : public glslang::TShader::Includer {
//public:
//    // For the "system" or <>-style includes; search the "system" paths.
//    IncludeResult* includeSystem(
//        const char* headerName, const char* /*includerName*/, size_t /*inclusionDepth*/) override {
//
//        for (auto& path : paths_) {
//            path.append(headerName);
//            IncludeResult* res = nullptr;
//            if ((res = get_include(path)) != nullptr) {
//                return res;
//            }
//        }
//
//        return nullptr;
//    }
//
//    // For the "local"-only aspect of a "" include. Should not search in the
//    // "system" paths, because on returning a failure, the parser will
//    // call includeSystem() to look in the "system" locations.
//    IncludeResult* includeLocal(
//        const char* headerName, const char* /*includerName*/, size_t /*inclusionDepth*/) override {
//        auto filename = local_path_;
//        filename.append(headerName);
//
//        return get_include(filename);
//    }
//
//    // Signals that the parser will no longer use the contents of the
//    // specified IncludeResult.
//    void releaseInclude(IncludeResult* res) override { delete[] res->headerData; }
//
//private:
//    [[nodiscard]] IncludeResult* get_include(std::filesystem::path const& filename) const {
//        if (std::filesystem::exists(filename)) {
//            std::ifstream file(filename);
//
//            auto const length = std::filesystem::file_size(filename);
//            auto const data = new char[length];
//            file.read(data, length);
//
//            file.close();
//
//            return new IncludeResult(filename.generic_string(), data, length, nullptr);
//        }
//
//        return nullptr;
//    }
//
//    std::filesystem::path local_path_;
//
//    std::vector<std::filesystem::path> paths_;
//};

} // end namespace shaderfactory
} // end namespace megamol
