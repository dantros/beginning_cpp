cmake_minimum_required(VERSION 3.20)
set(CMAKE_LEGACY_CYGWIN_WIN32 OFF)

project(code_as_static_library C CXX)

add_library(arrow_lib STATIC
    "arrow_functions.h"
    "arrow_functions.cpp"
    "arrow.h"
    "arrow.cpp"
    "point_functions.h"
    "point_functions.cpp"
    "point.h"
    "triangle.h"
    "triangle.cpp"
)

add_executable(main "main.cpp")
set_property(TARGET main PROPERTY CXX_STANDARD 20)

# Here we bind the library

## Headers are in this directory
target_include_directories(main PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

## We need the path to the librady binary
target_link_libraries(main PRIVATE arrow_lib)
