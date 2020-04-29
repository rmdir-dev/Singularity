cmake_minimum_required(VERSION 3.9)

find_program(CCACHE_PROGRAM ccache)
if(CCACHE_PROGRAM)
    set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE "${CCACHE_PROGRAM}")
endif()

project(SingularityEngine)

add_subdirectory(Core)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

file(GLOB_RECURSE testSrc
    "Singularity/src/*.h"
    "Singularity/src/*.cpp"
)


add_definitions(-DCORE_LOG_LEVEL=0)	

#-save-temps to generate assembly
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -std=c++17 -Wall -pedantic-errors")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -std=c++17 -Wall -pedantic-errors")

set(EXECUTABLE_OUTPUT_PATH
    build/${CMAKE_BUILD_TYPE}_x64/bin/)

#must be add here for Windows.
set(CORE_LIBS "${CMAKE_SOURCE_DIR}/Core/dep/libs/")
link_directories(${CORE_LIBS}/glew/GLEW-lib)
link_directories(${CORE_LIBS}/imgui/lib)

add_executable(SingularityEngine ${testSrc})

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT SingularityEngine)

file(COPY Assets/ DESTINATION ${EXECUTABLE_OUTPUT_PATH}/Assets)
file(COPY ValgrindDebugScript/ DESTINATION ${EXECUTABLE_OUTPUT_PATH})

target_link_libraries(SingularityEngine Core)