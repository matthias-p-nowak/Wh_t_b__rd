# starter project
project(starter)
message(STATUS "--- starter ----")

include_directories(.)

add_compile_options( -shared -rdynamic)

add_executable(starter main.cc)
set_target_properties(starter PROPERTIES VERSION 0.1)
target_link_libraries(starter dl)
add_precompiled_header(starter main.hh)

add_library(testLib SHARED module.cc)
set_target_properties(testLib PROPERTIES SOVERSION 0.1)
add_precompiled_header(testLib main.hh)
