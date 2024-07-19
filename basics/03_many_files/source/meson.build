project('many_files_project', 'cpp', default_options : ['cpp_std=c++20'])
src = [
    'main.cpp',
    'arrow_functions.cpp',
    'arrow.cpp',
    'point_functions.cpp',
    'triangle.cpp'
]
 
exe = executable('many_files', src, override_options : ['buildtype=release'] )
test('simple execution', exe)

# run at the terminal: 'meson setup ..\build_meson'
# and then build it with: 'meson compile -C ..\build_meson'
# once the code is compiled, you can run 'meson test' to execute the tests declared.

# you can also go to the build directory and execute: 'meson compile'
# or directly with something like ninja or Visual Studio
