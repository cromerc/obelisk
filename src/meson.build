obelisk_sources = files(
    'obelisk.cpp',
    'lexer.cpp',
    'parser.cpp',
    'knowledge_base.cpp'
)

sqlite3 = dependency('sqlite3')

subdir('ast')
obelisk_sources += obelisk_ast_sources

subdir('models')
obelisk_sources += obelisk_model_sources

executable('obelisk',
    obelisk_sources,
    dependencies : [sqlite3],
    install : true
)
