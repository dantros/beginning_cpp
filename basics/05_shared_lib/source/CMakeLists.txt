cmake_minimum_required(VERSION 3.4)
set(CMAKE_LEGACY_CYGWIN_WIN32 OFF)

project(code_as_shared_library C CXX)

# Problems building a shared library on windows? -> https://stackoverflow.com/questions/33062728/cmake-link-shared-library-on-windows

if(MSVC)
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS TRUE)
    set(BUILD_SHARED_LIBS TRUE)
endif()

# we don't need to specify headers, only source files
# headers are referenced from inside each cpp file
add_library(arrow_lib SHARED
    "arrow_functions.cpp"
    "arrow.cpp"
    "point_functions.cpp"
    "triangle.cpp"
)

include(GenerateExportHeader)
generate_export_header(arrow_lib)

add_executable(main "main.cpp")
set_property(TARGET main PROPERTY CXX_STANDARD 20)

# Here we bind the library

## Headers are in this directory
target_include_directories(main PRIVATE ${CMAKE_CURRENT_BINARY_DIR})

## We need the path to the library binary
target_link_libraries(main PRIVATE arrow_lib)
