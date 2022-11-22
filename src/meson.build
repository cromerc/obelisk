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

r = run_command('llvm-config', '--cppflags', check : true)
cpp_args = ' ' + r.stdout().replace('\n', ' ').replace('-I', '-isystem')

r = run_command('llvm-config', '--ldflags', '--system-libs', '--libs', 'core', check : true)
link_args = ' ' + r.stdout().replace('\n', ' ')

executable('obelisk',
    obelisk_sources,
    dependencies : [sqlite3],
    cpp_args : cpp_args.split(),
    link_args : link_args.split(),
    install : true
)
