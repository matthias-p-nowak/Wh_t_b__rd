set(_target whtbrd_dummy)
message("--- ${_target} ---")

qt5_wrap_cpp(MOCS dummy.hh)

add_library(${_target} SHARED dummy.cc ${MOCS})
set_target_properties(${_target} PROPERTIES SOVERSION ${Wh_t_b__rd_VERSION})
add_precompiled_header(${_target} dummy.hh)

add_dependencies(${_target} whtbrd_common)
qt5_use_modules(${_target} Core)
