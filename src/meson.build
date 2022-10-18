obelisk_sources = files(
    'obelisk.cpp',
    'lexer.cpp',
    'parser.cpp'
)

subdir('ast')
obelisk_sources += obelisk_ast_sources

executable('obelisk',
    obelisk_sources,
    install : true
)
