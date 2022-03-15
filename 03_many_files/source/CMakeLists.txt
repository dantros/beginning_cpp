cmake_minimum_required(VERSION 3.20)
set(CMAKE_LEGACY_CYGWIN_WIN32 OFF)

project(separate_files C CXX)

add_executable(main
    "main.cpp"
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

# We also could have done:
#set(SOURCES *.h *.cpp)
#add_executable(main ${SOURCES})

set_property(TARGET main PROPERTY CXX_STANDARD 20)
