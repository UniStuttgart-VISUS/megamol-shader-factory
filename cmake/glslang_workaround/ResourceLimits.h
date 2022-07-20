// This header allows us to find the symbol DefaultTBuiltInResource within the glslang-default-resource-limits.
// glslang currently does not have it in the public interface, making it impossible to access the default resources,
// i.e. when using vcpkg to get glslang
// Related glslang issue: https://github.com/KhronosGroup/glslang/issues/2822

#include <glslang/Public/ShaderLang.h>

namespace glslang {
extern const TBuiltInResource DefaultTBuiltInResource;
}
