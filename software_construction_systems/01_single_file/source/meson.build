project('hello_classes_project',
    'cpp',
    default_options : [
        'cpp_std=c++20',
        'backend=ninja',
        'buildtype=release'
    ])

# other buildtype options: plain, debug, debugoptimized, release, minsize, custom
# other backend options: ninja, vs, vs2010, vs2012, vs2013, vs2015, vs2017, vs2019, vs2022, xcode
# check the documentation at: https://mesonbuild.com/Builtin-options.html

demo_exec = executable('hello_classes', 'hello_classes.cpp')

# run at the terminal: 'meson setup ..\build_meson'
# and then build it with: 'meson compile -C ..\build_meson'
# you can also go to the build directory and execute: 'meson compile'
# or directly with something like ninja or Visual Studio depending on the backend used.

# once the code is compiled, you can run 'meson test' to execute the tests declared.
test('simple execution', demo_exec)
