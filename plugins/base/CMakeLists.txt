message("--- base plugin ---")


add_library(whtbrd_base SHARED base.cc)
set_target_properties(whtbrd_base PROPERTIES SOVERSION ${Wh_t_b__rd_VERSION})
add_precompiled_header(whtbrd_base base.hh)

