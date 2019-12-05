cmake_minimum_required(VERSION 3.9)

find_program(CCACHE_PROGRAM ccache)
if(CCACHE_PROGRAM)
    set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE "${CCACHE_PROGRAM}")
endif()

project(ImGUI)

file(GLOB_RECURSE ImGUI_SRC
    "*.h"
    "*.cpp")

set(LIBRARY_OUTPUT_PATH
    lib/)

link_directories(${CMAKE_SOURCE_DIR}../glew/lib)
link_directories(${CMAKE_SOURCE_DIR}../glfw/src)

add_library(ImGUI ${ImGUI_SRC})

target_link_libraries(ImGUI GLEW)
target_link_libraries(ImGUI glfw)


target_include_directories(ImGUI
        PRIVATE ../glfw/include)