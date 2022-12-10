project('obelisk',
    'cpp',
    version : '1.0.0',
    default_options : [
        'warning_level=3',
        'c_std=c17',
        'cpp_std=c++17'
    ]
)

doxygen = find_program('doxygen', required : false)
if not doxygen.found()
    error('MESON_SKIP_TEST doxygen not found.')
endif

cdata = configuration_data()
cdata.set('VERSION', meson.project_version())

if find_program('dot', required : false).found()
    cdata.set('HAVE_DOT', 'YES')
else
    cdata.set('HAVE_DOT', 'NO')
endif

subdir('doc')

subdir('src')
