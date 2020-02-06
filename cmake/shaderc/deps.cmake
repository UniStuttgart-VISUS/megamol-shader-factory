# dependencies for tag v2019.1

# glslang
execute_process(COMMAND ${GIT_EXECUTABLE} clone https://github.com/KhronosGroup/glslang.git "${SOURCE_DIR}/third_party/glslang"
ERROR_QUIET OUTPUT_STRIP_TRAILING_WHITESPACE)
execute_process(COMMAND ${GIT_EXECUTABLE} reset --hard 19ec0d2ff9059e8bc8ca0fc539597a771cefdc89
WORKING_DIRECTORY "${SOURCE_DIR}/third_party/glslang"
ERROR_QUIET OUTPUT_STRIP_TRAILING_WHITESPACE)

# SPIRV-Tools
execute_process(COMMAND ${GIT_EXECUTABLE} clone https://github.com/KhronosGroup/SPIRV-Tools.git "${SOURCE_DIR}/third_party/spirv-tools"
ERROR_QUIET OUTPUT_STRIP_TRAILING_WHITESPACE)
execute_process(COMMAND ${GIT_EXECUTABLE} reset --hard 1b3441036a8f178cb3b41c1aa222b652db522a88
WORKING_DIRECTORY "${SOURCE_DIR}/third_party/spirv-tools"
ERROR_QUIET OUTPUT_STRIP_TRAILING_WHITESPACE)

# SPIRV-Headers
execute_process(COMMAND ${GIT_EXECUTABLE} clone https://github.com/KhronosGroup/SPIRV-Headers.git "${SOURCE_DIR}/third_party/spirv-headers"
ERROR_QUIET OUTPUT_STRIP_TRAILING_WHITESPACE)
execute_process(COMMAND ${GIT_EXECUTABLE} reset --hard dc77030acc9c6fe7ca21fff54c5a9d7b532d7da6
WORKING_DIRECTORY "${SOURCE_DIR}/third_party/spirv-headers"
ERROR_QUIET OUTPUT_STRIP_TRAILING_WHITESPACE)
