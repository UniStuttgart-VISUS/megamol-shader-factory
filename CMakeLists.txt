cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

# Project
project(msf
  VERSION 0.1.0
  LANGUAGES CXX)

# Set a default build type if none was specified
if (NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  message(STATUS "Setting build type to 'Release' as none was specified.")
  set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build." FORCE)
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "RelWithDebInfo" "MinSizeRel")
endif ()

# Dependencies
include(cmake/libs.cmake)

# Utils
include(cmake/shaderc_utils.cmake)

# Options
option(BUILD_MSF_TEST "BUILD_MSF_TEST" OFF)

# Collect source files
file(GLOB_RECURSE public_header_files RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}" "include/*.h")
file(GLOB_RECURSE source_files RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}" "src/*.cpp")
file(GLOB_RECURSE header_files RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}" "src/*.h")

# Library
add_library(msf_static STATIC ${public_header_files} ${header_files} ${source_files})
target_compile_features(msf_static PUBLIC cxx_std_17)
set_target_properties(msf_static PROPERTIES
  CXX_EXTENSIONS OFF
  POSITION_INDEPENDENT_CODE ON)
target_link_libraries(msf_static PRIVATE glslang glslang-default-resource-limits)
target_include_directories(msf_static
  PUBLIC
    $<INSTALL_INTERFACE:include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src)

# Bundle with all glslang libs into a single static library
shaderc_combine_static_lib(msf_combined msf_static)
target_include_directories(msf_combined INTERFACE
  $<INSTALL_INTERFACE:include>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>)
if (NOT WIN32)
  # Required for glslang::osdependent
  find_package(Threads)
  target_link_libraries(msf_combined INTERFACE Threads::Threads)
endif ()

# Install
include(GNUInstallDirs)

install(DIRECTORY
  ${CMAKE_CURRENT_SOURCE_DIR}/include/
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

get_target_property(combined_lib_file msf_combined IMPORTED_LOCATION)
# Fix for Visual Studio, see: https://github.com/google/shaderc/blob/v2021.0/libshaderc/CMakeLists.txt#L101-L112
string(REGEX MATCH "Visual Studio .*" vs_generator "${CMAKE_GENERATOR}")
if (NOT "${vs_generator}" STREQUAL "")
  string(REPLACE "$(Configuration)" "\${CMAKE_INSTALL_CONFIG_NAME}" combined_lib_file_vs "${combined_lib_file}")
  install(FILES ${combined_lib_file_vs} DESTINATION ${CMAKE_INSTALL_LIBDIR})
else()
  install(FILES ${combined_lib_file} DESTINATION ${CMAKE_INSTALL_LIBDIR})
endif()

# Source groups in Visual Studio
set_target_properties(msf_static PROPERTIES FOLDER base)
foreach (FILE_NAME ${source_files})
  get_filename_component(FILE_PATH ${FILE_NAME} PATH)
  string(REPLACE "/" "\\" GROUP_NAME ${FILE_PATH})
  string(REGEX REPLACE "^src" "Source Files" GROUP_NAME ${GROUP_NAME})
  source_group(${GROUP_NAME} FILES ${FILE_NAME})
endforeach ()
foreach (FILE_NAME ${header_files})
  get_filename_component(FILE_PATH ${FILE_NAME} PATH)
  string(REPLACE "/" "\\" GROUP_NAME ${FILE_PATH})
  string(REGEX REPLACE "^src" "Header Files" GROUP_NAME ${GROUP_NAME})
  source_group(${GROUP_NAME} FILES ${FILE_NAME})
endforeach ()
foreach (FILE_NAME ${public_header_files})
  get_filename_component(FILE_PATH ${FILE_NAME} PATH)
  string(REPLACE "/" "\\" GROUP_NAME ${FILE_PATH})
  string(REGEX REPLACE "^include\\\\mmshader" "Public Header Files" GROUP_NAME ${GROUP_NAME})
  source_group(${GROUP_NAME} FILES ${FILE_NAME})
endforeach ()

# Test
if (BUILD_MSF_TEST)
  add_executable(mmshader_test test/main.cpp)
  target_link_libraries(mmshader_test PRIVATE msf_static)
  set_property(TARGET mmshader_test PROPERTY CXX_STANDARD 17)
  set_property(TARGET mmshader_test PROPERTY CXX_EXTENSIONS OFF)
endif ()
