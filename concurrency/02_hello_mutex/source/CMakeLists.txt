cmake_minimum_required(VERSION 3.20)
set(CMAKE_LEGACY_CYGWIN_WIN32 OFF)

project(hello_mutex_project C CXX)

add_executable(hello_mutex "hello_mutex.cpp")
set_property(TARGET hello_mutex PROPERTY CXX_STANDARD 20)