subdir('lib')

obelisk_sources = files(
    'main.cpp',
    'lexer.cpp',
    'parser.cpp'
)

sqlite3 = dependency('sqlite3')

subdir('ast')
obelisk_sources += obelisk_ast_sources

r = run_command('llvm-config', '--cppflags', check : true)
cpp_args = ' ' + r.stdout().replace('\n', ' ').replace('-I', '-isystem')

r = run_command('llvm-config', '--ldflags', '--system-libs', '--libs', 'core', check : true)
link_args = ' ' + r.stdout().replace('\n', ' ')

executable('obelisk',
    obelisk_sources,
    dependencies : [libobelisk, sqlite3],
    cpp_args : cpp_args.split(),
    link_args : link_args.split(),
    install : true
)
