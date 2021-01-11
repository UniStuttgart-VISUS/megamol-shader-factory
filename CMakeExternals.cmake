# Clone external script
if(NOT EXISTS "${CMAKE_BINARY_DIR}/script-externals")
  message(STATUS "Downloading external scripts")
  execute_process(COMMAND
    ${GIT_EXECUTABLE} clone -b v2.1 https://github.com/UniStuttgart-VISUS/megamol-cmake-externals.git script-externals --depth 1
    WORKING_DIRECTORY "${CMAKE_BINARY_DIR}"
    ERROR_QUIET OUTPUT_STRIP_TRAILING_WHITESPACE)
endif()

# Include external script
include("${CMAKE_BINARY_DIR}/script-externals/cmake/External.cmake")

function(require_external NAME)
  set(FETCHCONTENT_QUIET ON CACHE BOOL "")

  if(NAME STREQUAL "glslang")
    if(TARGET glslang)
      return()
    endif()

    if(WIN32)
      set(GLSLANG_LIB "lib/glslang.lib")
    else()
      include(GNUInstallDirs)
      set(GLSLANG_LIB "${CMAKE_INSTALL_LIBDIR}/glslang.a")
    endif()

    add_external_project(glslang STATIC
      GIT_REPOSITORY https://github.com/KhronosGroup/glslang.git
      GIT_TAG "11.1.0"
      BUILD_BYPRODUCTS "<INSTALL_DIR>/${GLSLANG_LIB}"
      CMAKE_ARGS
        -DBUILD_EXTERNAL=OFF
        -DBUILD_SHARED_LIBS=OFF
        -DBUILD_TESTING=OFF
        -DENABLE_CTEST=OFF
        -DENABLE_EXCEPTIONS=ON
        -DENABLE_GLSLANG_BINARIES=OFF
        -DENABLE_GLSLANG_JS=OFF
        -DENABLE_HLSL=OFF
        -DENABLE_OPT=OFF
        -DENABLE_PCH=OFF
        -DENABLE_RTTI=ON
        -DENABLE_SPVREMAPPER=OFF)

    add_external_library(glslang
      LIBRARY ${GLSLANG_LIB}      
      INTERFACE_LIBRARIES "${GLSLANG_LIB}")
  else()
    message(FATAL_ERROR "Unknown external required \"${NAME}\"")
  endif()

  mark_as_advanced(FORCE FETCHCONTENT_BASE_DIR)
  mark_as_advanced(FORCE FETCHCONTENT_FULLY_DISCONNECTED)
  mark_as_advanced(FORCE FETCHCONTENT_QUIET)
  mark_as_advanced(FORCE FETCHCONTENT_UPDATES_DISCONNECTED)
endfunction(require_external)