message("--- common ---")

# we have a PluginInterface
include_directories(.)
qt5_wrap_cpp(MOCS common.hh ${WHTBRD_INC}/whtbrd_show.hh)
add_library(whtbrd_common SHARED common.cc show.cc ${MOCS})
set_target_properties(whtbrd_common PROPERTIES SOVERSION ${Wh_t_b__rd_VERSION})
add_precompiled_header(whtbrd_common common.hh HDRS ${WHTBRD_INCS})

# does both include directories and libraries to link
qt5_use_modules(whtbrd_common Core)
