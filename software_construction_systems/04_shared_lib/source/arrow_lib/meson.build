
arrow_lib_sources = [
    'source/arrow_functions.cpp',
    'source/arrow.cpp',
    'source/point_functions.cpp',
    'source/triangle.cpp'
]
arrow_lib_include = include_directories('include')

# with the define ARROW_LIB, we add the __declspec(dllexport) / __declspec(dllexport) to the classes and
# functions of the public API of this shared library. Check 'arrow_lib_shared.h'
# Unlike CMake and premake, meson does not have a specific command, and only uses -DFOO notation given to the compiler
# Check https://github.com/mesonbuild/meson/issues/6269
arrow_lib = shared_library('arrow_lib',
    arrow_lib_sources,
    include_directories : arrow_lib_include,
    cpp_args : ['-DARROW_LIB']
)