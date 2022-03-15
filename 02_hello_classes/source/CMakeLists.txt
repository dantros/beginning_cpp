cmake_minimum_required(VERSION 3.20)
set(CMAKE_LEGACY_CYGWIN_WIN32 OFF)

project(hello_classes_project C CXX)

add_executable(hello_classes "hello_classes.cpp")
set_property(TARGET hello_classes PROPERTY CXX_STANDARD 20)