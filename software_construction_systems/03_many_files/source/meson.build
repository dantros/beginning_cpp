project('many_files_project',
    'cpp',
    default_options : [
        'cpp_std=c++20',
        'backend=ninja',
        'buildtype=release'
    ])

sources = [
    'main.cpp',
    'arrow_functions.cpp',
    'arrow.cpp',
    'point_functions.cpp',
    'triangle.cpp'
]

demo_exec = executable('many_files', sources)
test('simple execution', demo_exec)
