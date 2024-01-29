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
  URL "https://github.com/KhronosGroup/glslang/archive/14.0.0.tar.gz"
  URL_HASH SHA256=80bbb916a23e94ea9cbfb1acb5d1a44a7e0c9613bcf5b5947c03f2273bdc92b0)
FetchContent_GetProperties(glslang)
if (NOT glslang_POPULATED)
  message(STATUS "Fetch glslang ...")
  FetchContent_Populate(glslang)
  option(BUILD_EXTERNAL "" OFF)
  option(BUILD_SHARED_LIBS "" OFF)
  option(ENABLE_EXCEPTIONS "" ON)
  option(ENABLE_GLSLANG_BINARIES "" OFF)
  option(ENABLE_GLSLANG_JS "" OFF)
  option(ENABLE_HLSL "" OFF)
  option(ENABLE_OPT "" OFF)
  option(ENABLE_PCH "" ON)
  option(ENABLE_RTTI "" OFF)
  option(ENABLE_SPVREMAPPER "" OFF)
  option(GLSLANG_TESTS "" OFF)
  add_subdirectory(${glslang_SOURCE_DIR} ${glslang_BINARY_DIR} EXCLUDE_FROM_ALL)
  mark_as_advanced(FORCE
    FETCHCONTENT_SOURCE_DIR_GLSLANG
    FETCHCONTENT_UPDATES_DISCONNECTED_GLSLANG)
endif ()
