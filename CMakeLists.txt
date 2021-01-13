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

set(GLAD_PATH "." CACHE PATH "Path to glad install dir")
set(GLAD_INCLUDE "${GLAD_PATH}/include")
set(GLAD_LIB_PATH "${GLAD_PATH}/lib")

# Add externals
require_external(glslang)

# Collect source files
file(GLOB_RECURSE public_header_files RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}" "include/*.h" "include/*.inl")
file(GLOB_RECURSE source_files RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}" "src/*.cpp")
file(GLOB_RECURSE header_files RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}" "src/*.h")
#file(GLOB_RECURSE shader_files RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}" "Shaders/*")
#file(GLOB_RECURSE resource_files RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}" "Resources/*")

add_library(${PROJECT_NAME} STATIC ${public_header_files} ${header_files} ${source_files})
if (MSVC)
  target_compile_options(${PROJECT_NAME} PRIVATE "/MP" "/arch:SSE2" "/permissive-" "/Zc:rvalueCast" "/Wall" "/MD$<$<CONFIG:Debug>:d>")
  if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
        target_compile_options(${PROJECT_NAME} PRIVATE "-Wno-c++98-compat" "-Wno-c++98-c++11-compat" "-Wno-c++98-compat-pedantic" "-Xclang" "-pedantic")
  endif()
else()
  target_compile_options(${PROJECT_NAME} PRIVATE "-fPIC")
endif()
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_EXTENSIONS OFF)
target_link_directories(${PROJECT_NAME} PUBLIC ${GLAD_LIB_PATH})
target_link_libraries(${PROJECT_NAME} PUBLIC glslang::glslang glslang::genericcodegen glslang::machineindependent glslang::osdependent glslang::oglcompiler glad)
external_get_property(glslang INSTALL_DIR)
target_include_directories(${PROJECT_NAME}
    PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include> "src" "include" ${INSTALL_DIR}/include ${GLAD_INCLUDE})

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
install(DIRECTORY ${INSTALL_DIR}/include/ DESTINATION "include")
install(DIRECTORY ${INSTALL_DIR}/lib/ DESTINATION "lib")

if (BUILD_MSF_TEST)
  add_executable(mmshader_test test/main.cpp)
  #target_include_directories(mmshader_test PRIVATE ${PROJECT_NAME})
  target_link_libraries(mmshader_test PRIVATE ${PROJECT_NAME})
  set_property(TARGET mmshader_test PROPERTY CXX_STANDARD 17)
  set_property(TARGET mmshader_test PROPERTY CXX_EXTENSIONS OFF)
endif()
