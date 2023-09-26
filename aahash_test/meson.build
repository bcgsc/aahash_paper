src_files = [ 'aahash_test.cpp', 'city.cc', 'MurmurHash2.cpp', 'xxhash.c' ]
deps = [ openmp_dep, btllib_dep ]
link_args = [ '-lbtllib' ]


executable('aahash_test',
    src_files,
    dependencies : deps,
    install : true
)
