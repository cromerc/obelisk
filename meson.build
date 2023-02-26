project('obelisk',
    'c',
    'cpp',
    version : '1.0.0',
    license : 'BSD-3-Clause',
    default_options : [
        'warning_level=3',
        'c_std=c17',
        'cpp_std=c++17'
    ]
)

project_version_lib = '0'

llvm = dependency('llvm', version: '>= 14.0.0', modules : ['core', 'target', 'mcjit', 'nativecodegen'], required : true, method: 'config-tool')

cdata = configuration_data()
cdata.set('VERSION', meson.project_version())

docs_enabled = get_option('docs')
if docs_enabled
    doxygen = find_program('doxygen', required : false)
    if doxygen.found()
        if find_program('dot', required : false).found()
            cdata.set('HAVE_DOT', 'YES')
        else
            cdata.set('HAVE_DOT', 'NO')
        endif
        subdir('doc')
    endif
endif

subdir('sqlite')
subdir('src')
