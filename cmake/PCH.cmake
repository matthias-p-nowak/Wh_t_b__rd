# @Author Matthias P. Nowak
# @date 2018-12-14
# 
# Description
#
# This modules adds "add_precompiled_header(<target> <header>)"
# the header file has to be specified as a relative path from the 
# including CMakeLists.txt # in the c++ files, the header has to be 
# included as "#include <header>", since the module will prepend the 
# list of include directories with one in the build folder, where the 
# precompile header is generated.
# 
# This file is based on the work of Lars, only the GCC part is taken.
# Support is added for shared libraries. GCC can find a GCH-file before 
# finding the related header in another folder and recognises the 
# precompiled header.
#
# Caveats:
# - cmake is somewhat vague which properties are lists, and which ones 
#   are not.
#
# significant parts were taken from 
# https://github.com/larsch/cmake-precompiled-header
#
# Copyright (C) 2009-2017 Lars Christensen <larsch@belunktum.dk>
#
# Permission is hereby granted, free of charge, to any person
# obtaining a copy of this software and associated documentation files
# (the 'Software') deal in the Software without restriction,
# including without limitation the rights to use, copy, modify, merge,
# publish, distribute, sublicense, and/or sell copies of the Software,
# and to permit persons to whom the Software is furnished to do so,
# subject to the following conditions:
#
# The above copyright notice and this permission notice shall be
# included in all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED 'AS IS', WITHOUT WARRANTY OF ANY KIND,
# EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
# MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
# NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
# BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
# ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
# CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

message(STATUS "cmake function add_precompiled_header included")

#include("cmake/debugTarget.cmake")


function(add_precompiled_header _target _input)
  #message("got request for precompiled ${_input} for ${_target} lang ${lang}")
    if(CMAKE_COMPILER_IS_GNUCXX)
    if(COMMAND debugTarget)
      debugTarget(${_target})
    endif()
    get_filename_component(_name ${_input} NAME)
    #message(STATUS "name is ${_name}")
    set(_pch_header "${CMAKE_CURRENT_SOURCE_DIR}/${_input}")
    set(_pchdir "${CMAKE_CURRENT_BINARY_DIR}/${_target}_inc")
    set(_pchfile "${_pchdir}/${_name}.gch")
    file(MAKE_DIRECTORY "${_pchdir}")

    target_include_directories(${_target} BEFORE PUBLIC "${_pchdir}")

    set(_compile ${CMAKE_CXX_COMPILER})

    # returns true if <target> is a shared library
    get_property(_pic TARGET ${_target} PROPERTY POSITION_INDEPENDENT_CODE)
    if(_pic)
      get_property(_type TARGET ${_target} PROPERTY TYPE)
      if(${_type} STREQUAL "EXECUTABLE")
        list(APPEND _compile ${CMAKE_CXX_COMPILE_OPTIONS_PIE})
      elseif(${_type} STREQUAL "SHARED_LIBRARY")
        list(APPEND _compile ${CMAKE_CXX_COMPILE_OPTIONS_PIC} -D${_target}_EXPORTS)
      else()
        message("type ${_type}")
      endif()
    endif(_pic)


    set(_compile_flags)

    set(_props COMPILE_DEFINITIONS COMPILE_FEATURES COMPILE_FLAGS COMPILE_OPTIONS )
    foreach(_prop ${_props})
      #message("querying target ${_prop}")
      get_property(_cf TARGET ${_target} PROPERTY ${_prop})
      if(_cf)
        separate_arguments(_cf)
        list(APPEND _compile_flags ${_cf})
      endif()
    endforeach()
    
    get_property(_ext TARGET ${_target} PROPERTY CXX_STANDARD)
    if(_ext)
      list(APPEND _compile_flags ${CMAKE_CXX${_ext}_EXTENSION_COMPILE_OPTION})
    endif()
        
    set(_props COMPILE_DEFINITIONS COMPILE_FLAGS)
    
    get_property(_sources TARGET ${_target} PROPERTY SOURCES)    
    foreach(_source ${_sources})
      #message(STATUS "inspecting ${_source}")  
      foreach(_prop ${_props})
      get_property(_cf SOURCE ${_source} PROPERTY ${_prop})
      if(_cf)
        separate_arguments(_cf)
        list(APPEND _compile_flags ${_cf})
      endif()
      endforeach()
     
      get_source_file_property(_object_depends "${_source}" OBJECT_DEPENDS)
      if(NOT _object_depends)
        set(_object_depends)
      endif()
      list(INSERT _object_depends 0 "${_pchfile}")      
      set_source_files_properties(${_source} PROPERTIES
      OBJECT_DEPENDS "${_object_depends}")      
    endforeach()
    
    if(_compile_flags)
      list(REMOVE_DUPLICATES _compile_flags)
      #message("_compile_flags = ${_compile_flags}")
      list(APPEND _compile ${_compile_flags})
    endif()

    list(APPEND _compile "-o" "${_pchfile}" "${_pch_header}")

    #message("_compile is ${_compile}")
    add_custom_command(
      OUTPUT "${_pchfile}"
      COMMAND ${_compile} #it automatically expands the list to arguments
      DEPENDS "${_pch_header}"
      COMMENT "Precompiling ${_name} for ${_target} (C++)")
    
    target_compile_options(${_target} PUBLIC -Winvalid-pch -H)
   endif()
endfunction()
