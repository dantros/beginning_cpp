cmake_minimum_required(VERSION 3.20)
set(CMAKE_LEGACY_CYGWIN_WIN32 OFF)

project(hello_threads_project C CXX)

add_executable(hello_threads "hello_threads.cpp")
set_property(TARGET hello_threads PROPERTY CXX_STANDARD 20)