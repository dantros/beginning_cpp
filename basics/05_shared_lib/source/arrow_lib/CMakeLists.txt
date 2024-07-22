
# Do note that this is a shared library
add_library(arrow_library SHARED
    "source/arrow_functions.cpp"
    "source/arrow.cpp"
    "source/point_functions.cpp"
    "source/triangle.cpp"
)

target_include_directories(arrow_library PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include")