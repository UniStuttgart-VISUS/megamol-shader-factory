cmake_minimum_required(VERSION 3.12 FATAL_ERROR)

# Project
project(megamol-shader-factory CXX)

# Set a default build type if none was specified
if (NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  message(STATUS "Setting build type to 'Release' as none was specified.")
  set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build." FORCE)
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif ()

# Modules
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}/cmake)

# Dependencies
include("CMakeExternals.cmake")
require_external(glslang)

# Options
option(BUILD_MSF_TEST "BUILD_MSF_TEST" OFF)

option(GLAD_IS_SHARED "GLAD_IS_SHARED" OFF)
set(GLAD_PATH "." CACHE PATH "Path to glad install dir")
set(GLAD_INCLUDE "${GLAD_PATH}/include")
set(GLAD_LIB_PATH "${GLAD_PATH}/lib")

# Collect source files
file(GLOB_RECURSE public_header_files RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}" "include/*.h" "include/*.inl")
file(GLOB_RECURSE source_files RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}" "src/*.cpp")
file(GLOB_RECURSE header_files RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}" "src/*.h")

# Library
add_library(${PROJECT_NAME} STATIC ${public_header_files} ${header_files} ${source_files})
if (MSVC)
  target_compile_options(${PROJECT_NAME} PRIVATE "/MP" "/arch:SSE2" "/permissive-" "/Zc:rvalueCast" "/Wall" "/MD$<$<CONFIG:Debug>:d>")
  if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    target_compile_options(${PROJECT_NAME} PRIVATE "-Wno-c++98-compat" "-Wno-c++98-c++11-compat" "-Wno-c++98-compat-pedantic" "-Xclang" "-pedantic")
  endif ()
else ()
  target_compile_options(${PROJECT_NAME} PRIVATE "-fPIC")
endif ()
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_EXTENSIONS OFF)
target_link_directories(${PROJECT_NAME} PUBLIC ${GLAD_LIB_PATH})
target_link_libraries(${PROJECT_NAME} PUBLIC glslang::glslang glslang::machineindependent glslang::oglcompiler glslang::osdependent glslang::genericcodegen)
external_get_property(glslang INSTALL_DIR)
target_include_directories(${PROJECT_NAME}
  PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include> "src" "include" ${INSTALL_DIR}/include ${GLAD_INCLUDE})
if (GLAD_IS_SHARED)
  target_compile_definitions(${PROJECT_NAME} PUBLIC GLAD_GLAPI_EXPORT)
endif ()

# Source groups in Visual Studio
set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER base)
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

# Installation rules for generated files
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/ DESTINATION "include")
if (WIN32)
  install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION "bin")
  install(TARGETS ${PROJECT_NAME} ARCHIVE DESTINATION "lib")
else ()
  install(TARGETS ${PROJECT_NAME} DESTINATION "lib" EXPORT ${PROJECT_NAME}-target)
endif ()
install(DIRECTORY ${INSTALL_DIR}/include/ DESTINATION "include")
install(DIRECTORY ${INSTALL_DIR}/lib/ DESTINATION "lib")

# Test
if (BUILD_MSF_TEST)
  add_executable(mmshader_test test/main.cpp)
  target_link_libraries(mmshader_test PRIVATE ${PROJECT_NAME})
  if (NOT WIN32)
    # Required for glslang::osdependent
    find_package(Threads)
    target_link_libraries(mmshader_test PRIVATE Threads::Threads)
  endif ()
  set_property(TARGET mmshader_test PROPERTY CXX_STANDARD 17)
  set_property(TARGET mmshader_test PROPERTY CXX_EXTENSIONS OFF)
endif ()
