message("--- base plugin ---")

set(p_Base_inc "${CMAKE_CURRENT_SOURCE_DIR}/inc")

include_directories(inc ${CMAKE_HOME_DIRECTORY}/startup/inc)

set(BASE_src src/base.cc)

add_library(whtbrd_base SHARED ${BASE_src})
set_target_properties(whtbrd_base PROPERTIES SOVERSION ${Wh_t_b__rd_VERSION})
