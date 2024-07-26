cmake_minimum_required(VERSION 3.20)
set(CMAKE_LEGACY_CYGWIN_WIN32 OFF)

project(many_files_project CXX)

# we don't need to specify headers, only source files
# headers are referenced from inside each cpp file
add_executable(many_files
    "main.cpp"
    "arrow_functions.cpp"
    "arrow.cpp"
    "point_functions.cpp"
    "triangle.cpp"
)

set_property(TARGET many_files PROPERTY CXX_STANDARD 20)

# If you use CMaklePresets.json (you should as they are very convenient), you can list
# all presets with 'cmake --list-presets' and then execute the one you need with
# 'cmake -preset MY_PRESET'. You will get your project ready to build.