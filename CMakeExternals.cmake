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

  if(NAME STREQUAL "shaderc_combined")
    if(TARGET shaderc_combined)
      return()
    endif()

    if(WIN32)
      set(SHADERC_LIB "lib/shaderc_combined.lib")
    else()
      include(GNUInstallDirs)
      set(SHADERC_LIB "${CMAKE_INSTALL_LIBDIR}/libshaderc_combined.a")
    endif()

    add_external_project(shaderc_combined STATIC
      GIT_REPOSITORY https://github.com/google/shaderc.git
      GIT_TAG "v2020.2"
      BUILD_BYPRODUCTS "<INSTALL_DIR>/${SHADERC_LIB}"
      PATCH_COMMAND ${CMAKE_COMMAND} -D SOURCE_DIR=<SOURCE_DIR> -D GIT_EXECUTABLE=${GIT_EXECUTABLE} -P "${CMAKE_SOURCE_DIR}/cmake/shaderc/deps.cmake"
      CMAKE_ARGS
        -DSHADERC_SKIP_TESTS=ON
        -DSHADERC_ENABLE_SHARED_CRT=ON)

    add_external_library(shaderc_combined
      LIBRARY ${SHADERC_LIB}      
      INTERFACE_LIBRARIES "${SHADERC_LIB}")
  else()
    message(FATAL_ERROR "Unknown external required \"${NAME}\"")
  endif()

  mark_as_advanced(FORCE FETCHCONTENT_BASE_DIR)
  mark_as_advanced(FORCE FETCHCONTENT_FULLY_DISCONNECTED)
  mark_as_advanced(FORCE FETCHCONTENT_QUIET)
  mark_as_advanced(FORCE FETCHCONTENT_UPDATES_DISCONNECTED)
endfunction(require_external)