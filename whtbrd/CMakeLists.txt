message("--- whtbrd starter ---")

find_package(Qt5 COMPONENTS Core Widgets REQUIRED)

add_compile_options( )

include_directories(.)

# resource file compilation with the splash png
qt5_add_resources(QRCS startup.qrc)
# qt5_wrap_cpp(MOCS startup.hh)

add_executable(whtbrd startup.cc splash.cc ${QRCS} ${MOCS})
qt5_use_modules(whtbrd Widgets)
add_precompiled_header(whtbrd startup.hh HDRS splash.hh)
