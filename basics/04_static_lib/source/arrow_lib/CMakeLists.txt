
# We are listing each file independently as recommended by CMake creators
# ref: https://stackoverflow.com/questions/1027247/is-it-better-to-specify-source-files-with-glob-or-each-file-individually-in-cmak
# ref2: https://cmake.org/cmake/help/latest/command/file.html#glob

# we don't need to specify headers, only source files
# headers are referenced from inside each cpp file
add_library(arrow_library STATIC
    "sources/arrow_functions.cpp"
    "sources/arrow.cpp"
    "sources/point_functions.cpp"
    "sources/triangle.cpp"
)

# We need to tell this library where to look for the headers referenced in the source files
target_include_directories(arrow_library PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/includes")