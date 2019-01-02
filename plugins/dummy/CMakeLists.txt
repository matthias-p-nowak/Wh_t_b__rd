# 
# a bit more generalized CMake file good to copy 
#
set(_name dummy)

set(_target whtbrd_${_name})
message("--- ${_target} ---")

include_directories(.)

qt5_wrap_cpp(MOCS ${_name}.hh)
# add additional source files
add_library(${_target} SHARED ${_name}.cc ${MOCS})
qt5_use_modules(${_target} Widgets)
add_dependencies(${_target} whtbrd_common)
set_target_properties(${_target} PROPERTIES SOVERSION ${Wh_t_b__rd_VERSION})
# add additional header files
add_precompiled_header(${_target} ${_name}.hh HDRS )

