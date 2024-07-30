
# Do note that this is a SHARED library
add_library(arrow_library SHARED
    "source/arrow_functions.cpp"
    "source/arrow.cpp"
    "source/point_functions.cpp"
    "source/triangle.cpp"
)

# with this define, we add the __declspec(dllexport) / __declspec(dllexport) to the classes and
# functions of the public API of this shared library. Check 'arrow_lib_shared.h'
if(MSVC)
    target_compile_definitions(arrow_library PRIVATE ARROW_LIB=1)
endif()


target_include_directories(arrow_library PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include")