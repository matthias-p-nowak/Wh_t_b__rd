# ----- startup -----
message(" the startup project")

message("ok ${WHTBRD_VERSION}")

add_compile_options( -Wall)
include_directories(inc)

add_executable(whtbrd src/main.cc)
add_precompiled_header(whtbrd inc/startup.hh)
