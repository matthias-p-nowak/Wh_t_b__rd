message("--- workbench ---")

add_library(whtbrd_wb SHARED workbench.cc )
set_target_properties(whtbrd_wb PROPERTIES SOVERSION ${Wh_t_b__rd_VERSION})
add_precompiled_header(whtbrd_wb workbench.hh)

add_dependencies(whtbrd_wb whtbrd_common)
qt5_use_modules(whtbrd_wb Core)
