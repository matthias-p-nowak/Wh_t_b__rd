##
# 
# recommended:
# - mkdir build
# - cd build 
# - cmake -G Ninja ..
# - ninja
#####################
#
# cmake -Bbuild -H. -GNinja
#

cmake_minimum_required(VERSION 3.9)
project(Wh_t_b__rd VERSION 0.1)
message(STATUS "--- root ----")
include(cmake/PCH.cmake)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_BUILD_TYPE Debug)

# the global include file which all plugins need to know
set(WHTBRD_INC ${CMAKE_HOME_DIRECTORY}/include)
include_directories( ${WHTBRD_INC})
file(GLOB WHTBRD_INCS ${WHTBRD_INC}/*.hh )
add_definitions(-DWHTBRD_VERSION=${Wh_t_b__rd_VERSION} )

set(CMAKE_DEPFILE_FLAGS_${lang} "-MM -MT <OBJECT> -MF <DEPFILE>")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/plugins)

####

add_subdirectory(whtbrd)
add_subdirectory(plugins)

# 2 be deleted later on
