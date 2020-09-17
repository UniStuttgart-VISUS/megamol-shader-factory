#include "msf/compiler.h"

#include "msf/includer.h"

std::string megamol::shaderfactory::compiler::preprocess(
    std::filesystem::path const& shader_source_path, compiler_options const& options) const {
    std::filesystem::path final_shader_source_path;
    if (std::filesystem::exists(shader_source_path)) {
        final_shader_source_path = shader_source_path;
    } else if (shader_source_path.is_relative()) {
        bool found_path = false;
        for (auto const& el : options.get_shader_paths()) {
            auto final_shader_source_path = el;
            final_shader_source_path += shader_source_path;
            if (std::filesystem::exists(final_shader_source_path)) {
                if (found_path) {
                    return std::string();
                } else {
                    found_path = true;
                }
            }
        }
    } else {
        return std::string();
    }

    auto const shader_type = get_shader_type_sc(final_shader_source_path);

    auto const shader_source = read_shader_source(final_shader_source_path);

    auto const shader =
        compiler_.PreprocessGlsl(shader_source, shader_type, final_shader_source_path.string().c_str(), options);

    return std::string(shader.cbegin(), shader.cend());
}
