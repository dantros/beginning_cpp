cmake_minimum_required(VERSION 3.20)
set(CMAKE_LEGACY_CYGWIN_WIN32 OFF)

project(hello_concurrency_project C CXX)

add_executable(01_hello_threads "hello_threads.cpp")
set_property(TARGET 01_hello_threads PROPERTY CXX_STANDARD 20)

add_executable(02_hello_mutex "hello_mutex.cpp")
set_property(TARGET 02_hello_mutex PROPERTY CXX_STANDARD 20)

add_executable(03_hello_condition_variable "hello_condition_variable.cpp")
set_property(TARGET 03_hello_condition_variable PROPERTY CXX_STANDARD 20)

#add_executable(04_hello_async "hello_async.cpp")
#set_property(TARGET hello_async PROPERTY CXX_STANDARD 20)

#add_executable(05_hello_atomic "hello_atomic.cpp")
#set_property(TARGET hello_atomic PROPERTY CXX_STANDARD 20)