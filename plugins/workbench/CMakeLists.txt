message("--- workbench ---")

include_directories(.)

qt5_wrap_cpp(MOCS workbench.hh)
add_library(whtbrd_wb SHARED workbench.cc mainwindow.cc preview.cc fullscreen.cc ${MOCS})
qt5_use_modules(whtbrd_wb Widgets )
target_link_libraries(whtbrd_wb whtbrd_common)
set_target_properties(whtbrd_wb PROPERTIES SOVERSION ${Wh_t_b__rd_VERSION})
add_precompiled_header(whtbrd_wb workbench.hh HDRS mainwindow.hh fullscreen.hh preview.hh ${WHTBRD_INCS})
