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
  URL "https://github.com/KhronosGroup/glslang/archive/12.1.0.tar.gz"
  URL_HASH SHA256=1515e840881d1128fb6d831308433f731808f818f2103881162f3ffd47b15cd5)
FetchContent_GetProperties(glslang)
if (NOT glslang_POPULATED)
  message(STATUS "Fetch glslang ...")
  FetchContent_Populate(glslang)
  option(BUILD_EXTERNAL "" OFF)
  option(BUILD_SHARED_LIBS "" OFF)
  option(ENABLE_CTEST "" OFF)
  option(ENABLE_EXCEPTIONS "" ON)
  option(ENABLE_GLSLANG_BINARIES "" OFF)
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
