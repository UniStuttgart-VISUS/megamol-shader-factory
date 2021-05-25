# Dependencies

# Setup FetchContent
include(FetchContent)
mark_as_advanced(FORCE
  FETCHCONTENT_BASE_DIR
  FETCHCONTENT_FULLY_DISCONNECTED
  FETCHCONTENT_QUIET
  FETCHCONTENT_UPDATES_DISCONNECTED)

# glslang
FetchContent_Declare(glslang
  GIT_REPOSITORY https://github.com/KhronosGroup/glslang.git
  GIT_TAG 11.4.0)
FetchContent_GetProperties(glslang)
if (NOT glslang_POPULATED)
  FetchContent_Populate(glslang)
  option(BUILD_EXTERNAL "" OFF)
  option(BUILD_SHARED_LIBS "" OFF)
  option(ENABLE_CTEST "" OFF)
  option(ENABLE_EXCEPTIONS "" ON)
  option(ENABLE_GLSLANG_BINARIES "" ON) # required for target glslang-default-resource-limits
  option(ENABLE_GLSLANG_JS "" OFF)
  option(ENABLE_HLSL "" OFF)
  option(ENABLE_OPT "" OFF)
  option(ENABLE_PCH "" ON)
  option(ENABLE_RTTI "" OFF)
  option(ENABLE_SPVREMAPPER "" OFF)
  mark_as_advanced(FORCE
    FETCHCONTENT_SOURCE_DIR_GLSLANG
    FETCHCONTENT_UPDATES_DISCONNECTED_GLSLANG)
  add_subdirectory(${glslang_SOURCE_DIR} ${glslang_BINARY_DIR} EXCLUDE_FROM_ALL)
endif ()
