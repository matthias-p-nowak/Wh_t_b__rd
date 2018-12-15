# starter project
project(starter)
message(STATUS "--- starter ----")

include_directories(include)

add_executable(starter src/main.cc)
set_target_properties(starter PROPERTIES VERSION 0.1)
target_link_libraries(starter dl)
add_precompiled_header(starter include/main.hh)

add_library(testLib SHARED src/module.cc)
set_target_properties(testLib PROPERTIES SOVERSION 0.1)
add_precompiled_header(testLib include/main.hh)
