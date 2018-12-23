message("--- common ---")

qt5_wrap_cpp(MOCS common.hh)
add_library(whtbrd_common SHARED common.cc ${MOCS})

set_target_properties(whtbrd_common PROPERTIES SOVERSION ${Wh_t_b__rd_VERSION})
add_precompiled_header(whtbrd_common common.hh)

qt5_use_modules(whtbrd_common Core)
