# ----- startup -----
message(" the old startup project")

# message("ok ${WHTBRD_VERSION}")

add_compile_options( -Wall)

add_executable(whtbrd2 main.cc)
target_link_libraries(whtbrd2 dl)
add_precompiled_header(whtbrd2 startup.hh)
