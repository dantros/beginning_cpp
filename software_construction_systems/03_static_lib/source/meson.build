project('code_as_static_library',
    'cpp',
    default_options : [
        'cpp_std=c++20',
        'backend=ninja',
        'buildtype=release'
    ])

# Everything defined at arrow_lib/meson.build will be available after the subdir command.
# Similarly, everything defined up to here, will be available inside arrow_lib/meson.build
subdir('arrow_lib')
 
demo_exec = executable('static_lib_demo',
    'main.cpp',
    link_with : arrow_lib,
    include_directories : arrow_lib_include
)
test('simple execution', demo_exec)
