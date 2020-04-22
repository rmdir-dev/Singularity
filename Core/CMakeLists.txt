cmake_minimum_required(VERSION 3.9)

find_program(CCACHE_PROGRAM ccache)
if(CCACHE_PROGRAM)
    set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE "${CCACHE_PROGRAM}")
endif()

project (Core)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(dep/libs/glfw)
#add_subdirectory(dep/libs/imgui)
add_subdirectory(dep/libs/assimp2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

file(GLOB_RECURSE ehSRC
    "src/*.h"
    "src/*.cpp"
    "src/*.c"
)

set(LIBRARY_OUTPUT_PATH
    build/${CMAKE_BUILD_TYPE}/lib/)

add_definitions(-DCORE_LOG_LEVEL=0 -DGLEW_STATIC)

link_directories(${CMAKE_SOURCE_DIR}/dep/libs/glew/GLEW-lib)

#-save-temps to generate assembly
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -std=c++17 -Wall -pedantic-errors")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -std=c++17 -Wall -pedantic-errors")

add_library(Core ${ehSRC})

target_include_directories(Core 
    PUBLIC src
    PUBLIC dep/includes)

target_link_libraries(Core glfw)
#target_link_libraries(Core ImGUI)
target_link_libraries(Core assimp)

find_package(OpenGL REQUIRED)
target_include_directories(Core PUBLIC ${OPENGL_INCLUDE_DIR})
target_link_libraries(Core ${OPENGL_gl_LIBRARY})
target_link_libraries(Core ${OPENGL_glu_LIBRARY})

find_package(Vulkan REQUIRED)
target_include_directories(Core PRIVATE Vulkan::Vulkan)
target_link_libraries(Core Vulkan::Vulkan)

target_link_libraries(Core GLEW)