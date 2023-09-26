project('aahash_test', 'cpp', 'c',
        version : '1.0.0',
        license : 'GPL-3',
        default_options : [ 'cpp_std=c++17', 'warning_level=3', 'werror=true' ])


openmp_dep = dependency('openmp')



compiler = meson.get_compiler('cpp')
btllib_dep = compiler.find_library('btllib')


add_project_arguments(
'-Wno-error=implicit-fallthrough=',
'-Wno-error=vla',
language : 'cpp'
)

add_project_arguments(
'-Wno-error=implicit-function-declaration',
language : 'c'
)


subdir('aahash_test')

rootpath = meson.source_root()

