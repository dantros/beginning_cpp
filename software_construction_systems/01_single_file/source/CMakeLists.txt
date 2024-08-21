cmake_minimum_required(VERSION 3.20)

project(hello_classes_project CXX)

add_executable(hello_classes "hello_classes.cpp")
set_property(TARGET hello_classes PROPERTY CXX_STANDARD 20)

# If you use CMakePresets.json (you should as they are very convenient), you can list
# all presets with 'cmake --list-presets' and then execute the one you need with
# 'cmake --preset MY_PRESET'. You will get your project ready to build.