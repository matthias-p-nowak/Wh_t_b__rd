##
# 
# recommended:
# - mkdir build
# - cd build 
# - cmake -G Ninja ..
# - ninja
#####################
cmake_minimum_required(VERSION 3.9)
project(Wh_t_b__rd)
message(STATUS "--- root ----")
include(cmake/PCH.cmake)
set(CMAKE_CXX_STANDARD 11)
# the global include file which all plugins need to know
include_directories(include)

set(WHTBRD_MAJOR 0)
set(WHTBRD_MINOR 1)
set(WHTBRD_VERSION ${WHTBRD_MAJOR}.${WHTBRD_MINOR})
add_definitions(-DFOO -DBAR )

add_subdirectory(starter)
add_subdirectory(startup)
