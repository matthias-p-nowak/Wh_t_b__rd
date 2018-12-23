message("--- plugins ---")


find_package(Qt5 COMPONENTS Core Widgets REQUIRED)


add_subdirectory(common)
add_subdirectory(workbench)

add_subdirectory(plug1)
add_subdirectory(base)

