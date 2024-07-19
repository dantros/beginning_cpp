cmake_minimum_required(VERSION 3.20)
set(CMAKE_LEGACY_CYGWIN_WIN32 OFF)

project(many_files_project CXX)

add_executable(many_files
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

set_property(TARGET many_files PROPERTY CXX_STANDARD 20)

# If you use CMaklePresets.json (you should as they are very convenient), you can list
# all presets with 'cmake --list-presets' and then execute the one you need with
# 'cmake -preset MY_PRESET'. You will get your project ready to build.