# dependencies for tag v2020.2

# glslang
execute_process(COMMAND ${GIT_EXECUTABLE} clone https://github.com/KhronosGroup/glslang.git "${SOURCE_DIR}/third_party/glslang"
  ERROR_QUIET OUTPUT_STRIP_TRAILING_WHITESPACE)
execute_process(COMMAND ${GIT_EXECUTABLE} reset --hard 3ee5f2f1d3316e228916788b300d786bb574d337
  WORKING_DIRECTORY "${SOURCE_DIR}/third_party/glslang"
  ERROR_QUIET OUTPUT_STRIP_TRAILING_WHITESPACE)

# SPIRV-Tools
execute_process(COMMAND ${GIT_EXECUTABLE} clone https://github.com/KhronosGroup/SPIRV-Tools.git "${SOURCE_DIR}/third_party/spirv-tools"
  ERROR_QUIET OUTPUT_STRIP_TRAILING_WHITESPACE)
execute_process(COMMAND ${GIT_EXECUTABLE} reset --hard 969f0286479b89267b6c89f6d5223285c265e6ae
  WORKING_DIRECTORY "${SOURCE_DIR}/third_party/spirv-tools"
  ERROR_QUIET OUTPUT_STRIP_TRAILING_WHITESPACE)

# SPIRV-Headers
execute_process(COMMAND ${GIT_EXECUTABLE} clone https://github.com/KhronosGroup/SPIRV-Headers.git "${SOURCE_DIR}/third_party/spirv-headers"
  ERROR_QUIET OUTPUT_STRIP_TRAILING_WHITESPACE)
execute_process(COMMAND ${GIT_EXECUTABLE} reset --hard 979924c8bc839e4cb1b69d03d48398551f369ce7
  WORKING_DIRECTORY "${SOURCE_DIR}/third_party/spirv-headers"
  ERROR_QUIET OUTPUT_STRIP_TRAILING_WHITESPACE)
