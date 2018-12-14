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

add_subdirectory(starter)
