message("--- plug 1 ---")

message("base_inc is ${p_Base_inc}") #not remembered

include_directories(../base/inc )

add_library(whtbrd_plug1 SHARED plug1.cc )
add_dependencies(whtbrd_plug1 whtbrd_base)
