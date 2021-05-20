# Copied from:
# https://github.com/google/shaderc/blob/v2021.0/cmake/utils.cmake

# Copyright 2020 The Shaderc Authors. All rights reserved.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

# utility functions

# Finds all transitive static library dependencies of a given target
# including possibly the target itself.
# This will skip libraries that were statically linked that were not
# built by CMake, for example -lpthread.
macro(shaderc_get_transitive_libs target out_list)
  if (TARGET ${target})
    get_target_property(libtype ${target} TYPE)
    # If this target is a static library, get anything it depends on.
    if ("${libtype}" STREQUAL "STATIC_LIBRARY")
      # Get the original library if this is an alias library. This is
      # to avoid putting both the original library and the alias library
      # in the list (given we are deduplicating according to target names).
      # Otherwise, we may pack the same library twice, resulting in
      # duplicated symbols.
      get_target_property(aliased_target ${target} ALIASED_TARGET)
      if (aliased_target)
        list(INSERT ${out_list} 0 "${aliased_target}")
      else()
        list(INSERT ${out_list} 0 "${target}")
      endif()

      get_target_property(libs ${target} LINK_LIBRARIES)
      if (libs)
        foreach(lib ${libs})
          shaderc_get_transitive_libs(${lib} ${out_list})
        endforeach()
      endif()
    endif()
  endif()
  # If we know the location (i.e. if it was made with CMake) then we
  # can add it to our list.
  LIST(REMOVE_DUPLICATES ${out_list})
endmacro()

# Combines the static library "target" with all of its transitive static
# library dependencies into a single static library "new_target".
function(shaderc_combine_static_lib new_target target)

  set(all_libs "")
  shaderc_get_transitive_libs(${target} all_libs)

  set(libname
      ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/${CMAKE_STATIC_LIBRARY_PREFIX}${new_target}${CMAKE_STATIC_LIBRARY_SUFFIX})

  if (MSVC)
    string(REPLACE ";" ">;$<TARGET_FILE:" temp_string "${all_libs}")
    set(lib_target_list "$<TARGET_FILE:${temp_string}>")

    add_custom_command(OUTPUT ${libname}
      DEPENDS ${all_libs}
      COMMAND lib.exe ${lib_target_list} /OUT:${libname} /NOLOGO)
  elseif(APPLE)
    string(REPLACE ";" ">;$<TARGET_FILE:" temp_string "${all_libs}")
    set(lib_target_list "$<TARGET_FILE:${temp_string}>")

    add_custom_command(OUTPUT ${libname}
      DEPENDS ${all_libs}
      COMMAND libtool -static -o ${libname} ${lib_target_list})
  else()
    string(REPLACE ";" "> \naddlib $<TARGET_FILE:" temp_string "${all_libs}")
    set(start_of_file
      "create ${libname}\naddlib $<TARGET_FILE:${temp_string}>")
    set(build_script_file "${start_of_file}\nsave\nend\n")

    file(GENERATE OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/${new_target}.ar"
        CONTENT ${build_script_file}
        CONDITION 1)

    add_custom_command(OUTPUT  ${libname}
      DEPENDS ${all_libs}
      COMMAND ${CMAKE_AR} -M < ${new_target}.ar)
  endif()

  add_custom_target(${new_target}_genfile ALL
    DEPENDS ${libname})

  # CMake needs to be able to see this as another normal library,
  # so import the newly created library as an imported library,
  # and set up the dependencies on the custom target.
  add_library(${new_target} STATIC IMPORTED)
  set_target_properties(${new_target}
    PROPERTIES IMPORTED_LOCATION ${libname})
  add_dependencies(${new_target} ${new_target}_genfile)
endfunction()
