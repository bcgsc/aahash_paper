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

btllib_include = [ include_directories('include'), include_directories('.') ]
btllib_sources = run_command('scripts/get-files', 'src').stdout().strip().split()

btllib_lib = static_library('btllib',
                           btllib_sources,
                           include_directories : btllib_include,
                           install : true,
                           install_dir : 'lib')

subdir('aahash_seed_gen')
subdir('aahash_test')
subdir('bin')
subdir('include')

rootpath = meson.source_root()

