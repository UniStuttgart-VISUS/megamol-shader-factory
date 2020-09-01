cmake_minimum_required(VERSION 3.12 FATAL_ERROR)

set(CMAKE_CONFIGURATION_TYPES "Debug;Release;RelWithDebInfo" CACHE STRING "Possible Build Types" FORCE)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Choose Release or Debug" FORCE)
endif()

option(BUILD_MSF_TEST "BUILD_MSF_TEST" OFF)

project(megamol-shader-factory CXX)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}/cmake)

find_package(Git)

# External
include("CMakeExternals.cmake")

add_subdirectory(glad)

# Add externals
require_external(shaderc)

# Collect source files
file(GLOB_RECURSE public_header_files RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}" "include/*.h" "include/*.inl")
file(GLOB_RECURSE source_files RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}" "src/*.cpp")
file(GLOB_RECURSE header_files RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}" "src/*.h")
#file(GLOB_RECURSE shader_files RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}" "Shaders/*")
#file(GLOB_RECURSE resource_files RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}" "Resources/*")

if (MSVC)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP /arch:SSE2 /permissive- /Zc:rvalueCast /Wall")
  set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MDd")
  set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MD")
  if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-c++98-compat -Wno-c++98-c++11-compat -Wno-c++98-compat-pedantic -Xclang -pedantic")
  endif()
endif()

add_library(${PROJECT_NAME} STATIC ${public_header_files} ${header_files} ${source_files})
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_EXTENSIONS OFF)
target_include_directories(${PROJECT_NAME}
    PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include> "src" "include")
target_link_libraries(${PROJECT_NAME} PUBLIC shaderc glad)

# Source groups in Visual Studio
set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER base)
foreach(FILE_NAME ${source_files})
  get_filename_component(FILE_PATH ${FILE_NAME} PATH)
  string(REPLACE "/" "\\" GROUP_NAME ${FILE_PATH})
  string(REGEX REPLACE "^src" "Source Files" GROUP_NAME ${GROUP_NAME})
  source_group(${GROUP_NAME} FILES ${FILE_NAME})
endforeach()
foreach(FILE_NAME ${header_files})
  get_filename_component(FILE_PATH ${FILE_NAME} PATH)
  string(REPLACE "/" "\\" GROUP_NAME ${FILE_PATH})
  string(REGEX REPLACE "^src" "Header Files" GROUP_NAME ${GROUP_NAME})
  source_group(${GROUP_NAME} FILES ${FILE_NAME})
endforeach()
foreach(FILE_NAME ${public_header_files})
  get_filename_component(FILE_PATH ${FILE_NAME} PATH)
  string(REPLACE "/" "\\" GROUP_NAME ${FILE_PATH})
  string(REGEX REPLACE "^include\\\\mmshader" "Public Header Files" GROUP_NAME ${GROUP_NAME})
  source_group(${GROUP_NAME} FILES ${FILE_NAME})
endforeach()

# Installation rules for generated files
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/ DESTINATION "include")
if(WIN32)
  install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION "bin")
  install(TARGETS ${PROJECT_NAME} ARCHIVE DESTINATION "lib")
else()
  install(TARGETS ${PROJECT_NAME} DESTINATION "lib" EXPORT ${PROJECT_NAME}-target)
endif()
get_target_property(shaderc_include shaderc INTERFACE_INCLUDE_DIRECTORIES)
install(DIRECTORY ${shaderc_include}/shaderc DESTINATION ${CMAKE_INSTALL_PREFIX} FILES_MATCHING PATTERN "*.h*")

if (BUILD_MSF_TEST)
  add_executable(mmshader_test test/main.cpp)
  #target_include_directories(mmshader_test PRIVATE ${PROJECT_NAME})
  target_link_libraries(mmshader_test PRIVATE ${PROJECT_NAME})
  set_property(TARGET mmshader_test PROPERTY CXX_STANDARD 17)
  set_property(TARGET mmshader_test PROPERTY CXX_EXTENSIONS OFF)
endif()
