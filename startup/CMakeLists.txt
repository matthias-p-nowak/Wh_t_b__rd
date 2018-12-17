# ----- startup -----
message(" the startup project")

message("ok ${WHTBRD_VERSION}")

add_compile_options( -Wall)
include_directories(.)

add_executable(whtbrd main.cc)
target_link_libraries(whtbrd dl)
add_precompiled_header(whtbrd startup.hh)
