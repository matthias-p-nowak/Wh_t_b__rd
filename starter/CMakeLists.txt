# starter project
project(starter)
message(STATUS "--- starter ----")

include_directories(include)

add_executable(starter src/main.cc)
target_link_libraries(starter dl)
add_precompiled_header(starter include/main.hh)

add_library(testLib SHARED src/module.cc)
add_precompiled_header(testLib include/main.hh)
