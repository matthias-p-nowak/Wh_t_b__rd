##
# 
# recommended:
# - mkdir build
# - cd build 
# - cmake -G Ninja ..
# - ninja
#####################
cmake_minimum_required(VERSION 3.9)
project(Wh_t_b__rd VERSION 0.1)
message(STATUS "--- root ----")
include(cmake/PCH.cmake)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_BUILD_TYPE Debug)

# the global include file which all plugins need to know
include_directories(include)
add_definitions(-DWHTBRD_VERSION=${Wh_t_b__rd_VERSION} )

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_subdirectory(startup)

add_subdirectory(plugins)

# 2 be deleted later on
