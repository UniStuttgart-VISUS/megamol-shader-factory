#include "msf/compiler.h"

#include "includer.h"

std::string megamol::shaderfactory::compiler::preprocess(
    std::filesystem::path const& shader_source_path, shaderc::CompileOptions const& options) const {
    if (std::filesystem::exists(shader_source_path)) {
        auto const shader_type_string = shader_source_path.stem().extension().string();

        auto const shader_type = parse_type_string(shader_type_string);

        auto const shader_source = read_shader_source(shader_source_path);

        auto const shader =
            compiler_.PreprocessGlsl(shader_source, shader_type, shader_source_path.string().c_str(), options);

        return std::string(shader.cbegin(), shader.cend());
    }

    return std::string();
}
