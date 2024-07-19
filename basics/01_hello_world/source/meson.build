project('hello_world_project', 'cpp', default_options : ['cpp_std=c++20'])

# other build type options ...
# override_options : ['buildtype=debug'] 
# override_options : ['buildtype=debugoptimized']
exe = executable('hello_world', 'hello_world.cpp', override_options : ['buildtype=release'])
test('simple execution', exe)

# run at the terminal: 'meson setup ..\build_meson'
# and then build it with: 'meson compile -C ..\build_meson'
# once the code is compiled, you can run 'meson test' to execute the tests declared.

# you can also go to the build directory and execute: 'meson compile'
# or directly with something like ninja or Visual Studio