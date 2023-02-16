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
  GIT_TAG 12.0.0)
FetchContent_GetProperties(glslang)
if (NOT glslang_POPULATED)
  message(STATUS "Fetch glslang ...")
  FetchContent_Populate(glslang)
  option(BUILD_EXTERNAL "" OFF)
  option(BUILD_SHARED_LIBS "" OFF)
  option(ENABLE_CTEST "" OFF)
  option(ENABLE_EXCEPTIONS "" ON)
  option(ENABLE_GLSLANG_BINARIES "" OFF) # see comment about glslang-default-resource-limits below
  option(ENABLE_GLSLANG_JS "" OFF)
  option(ENABLE_HLSL "" OFF)
  option(ENABLE_OPT "" OFF)
  option(ENABLE_PCH "" ON)
  option(ENABLE_RTTI "" OFF)
  option(ENABLE_SPVREMAPPER "" OFF)
  add_subdirectory(${glslang_SOURCE_DIR} ${glslang_BINARY_DIR} EXCLUDE_FROM_ALL)
  mark_as_advanced(FORCE
    FETCHCONTENT_SOURCE_DIR_GLSLANG
    FETCHCONTENT_UPDATES_DISCONNECTED_GLSLANG)
endif ()

# We want to use glslang-default-resource-limits which is included with ENABLE_GLSLANG_BINARIES. Unfortunately, other
# targets also enabled with ENABLE_GLSLANG_BINARIES require Python which we do not want as hard dependency of the
# shader factory. Therefore, we manually create the glslang-default-resource-limits target here without enabling
# ENABLE_GLSLANG_BINARIES.

add_library(glslang-default-resource-limits STATIC EXCLUDE_FROM_ALL
  ${glslang_SOURCE_DIR}/StandAlone/ResourceLimits.cpp
  ${glslang_SOURCE_DIR}/StandAlone/resource_limits_c.cpp)
set_property(TARGET glslang-default-resource-limits PROPERTY FOLDER glslang)
set_property(TARGET glslang-default-resource-limits PROPERTY POSITION_INDEPENDENT_CODE ON)

target_include_directories(glslang-default-resource-limits
  PUBLIC $<BUILD_INTERFACE:${glslang_SOURCE_DIR}>)
