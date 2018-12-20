message("--- plug 1 ---")

add_library(whtbrd_plug1 SHARED plug1.cc )
set_target_properties(whtbrd_plug1 PROPERTIES SOVERSION ${Wh_t_b__rd_VERSION})
add_precompiled_header(whtbrd_plug1 plug1.hh)

add_dependencies(whtbrd_plug1 whtbrd_base)
qt5_use_modules(whtbrd_plug1 Core)
