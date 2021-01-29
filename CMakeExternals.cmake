# Clone external script
if(NOT EXISTS "${CMAKE_BINARY_DIR}/script-externals")
  message(STATUS "Downloading external scripts")
  execute_process(COMMAND
    ${GIT_EXECUTABLE} clone -b v2.2 https://github.com/UniStuttgart-VISUS/megamol-cmake-externals.git script-externals --depth 1
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
      set(GLSLANG_LIB "lib/glslang<SUFFIX>.lib")
      set(GENERICCODEGEN_LIB "lib/GenericCodeGen<SUFFIX>.lib")
      set(MACHINEINDEPENDENT_LIB "lib/MachineIndependent<SUFFIX>.lib")
      set(OSDEPENDENT_LIB "lib/OSDependent<SUFFIX>.lib")
      set(OGLCOMPILER_LIB "lib/OGLCompiler<SUFFIX>.lib")
      set(SPIRV_LIB "lib/SPIRV<SUFFIX>.lib")
    else()
      include(GNUInstallDirs)
      set(GLSLANG_LIB "${CMAKE_INSTALL_LIBDIR}/libglslang.a")
      set(GENERICCODEGEN_LIB "lib/libGenericCodeGen.a")
      set(MACHINEINDEPENDENT_LIB "lib/libMachineIndependent.a")
      set(OSDEPENDENT_LIB "lib/libOSDependent.a")
      set(OGLCOMPILER_LIB "lib/libOGLCompiler.a")
      set(SPIRV_LIB "lib/libSPIRV.a")
    endif()

    add_external_project(glslang STATIC
      GIT_REPOSITORY https://github.com/KhronosGroup/glslang.git
      GIT_TAG "11.1.0"
      BUILD_BYPRODUCTS "<INSTALL_DIR>/${GLSLANG_LIB}" "<INSTALL_DIR>/${SPIRV_LIB}" "<INSTALL_DIR>/${MACHINEINDEPENDENT_LIB}" "<INSTALL_DIR>/${OGLCOMPILER_LIB}" "<INSTALL_DIR>/${OSDEPENDENT_LIB}" "<INSTALL_DIR>/${GENERICCODEGEN_LIB}"
      DEBUG_SUFFIX "d"
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

    add_external_library(glslang::glslang
      PROJECT glslang
      LIBRARY ${GLSLANG_LIB}
      DEBUG_SUFFIX "d")
    add_external_library(glslang::genericcodegen
      PROJECT glslang
      LIBRARY ${GENERICCODEGEN_LIB}
      DEBUG_SUFFIX "d")
    add_external_library(glslang::machineindependent
      PROJECT glslang
      LIBRARY ${MACHINEINDEPENDENT_LIB}
      DEBUG_SUFFIX "d")
    add_external_library(glslang::osdependent
      PROJECT glslang
      LIBRARY ${OSDEPENDENT_LIB}
      DEBUG_SUFFIX "d")
    add_external_library(glslang::oglcompiler
      PROJECT glslang
      LIBRARY ${OGLCOMPILER_LIB}
      DEBUG_SUFFIX "d")
    add_external_library(glslang::spirv
      PROJECT glslang
      LIBRARY ${SPIRV_LIB}
      DEBUG_SUFFIX "d")
  else()
    message(FATAL_ERROR "Unknown external required \"${NAME}\"")
  endif()

  mark_as_advanced(FORCE FETCHCONTENT_BASE_DIR)
  mark_as_advanced(FORCE FETCHCONTENT_FULLY_DISCONNECTED)
  mark_as_advanced(FORCE FETCHCONTENT_QUIET)
  mark_as_advanced(FORCE FETCHCONTENT_UPDATES_DISCONNECTED)
endfunction(require_external)