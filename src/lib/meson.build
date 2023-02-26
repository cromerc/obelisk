conf_data = configuration_data()
conf_data.set('version', meson.project_version())
conf_data.set('so_version', project_version_lib)
configure_file(input : 'version.h.in',
    output : 'version.h',
    configuration : conf_data
)

subdir('models')

obelisk_lib_sources = files(
    'obelisk.cpp',
    'obelisk.c',
    'obelisk_wrapper.cpp',
    'knowledge_base.cpp'
)

obelisk_lib_sources += obelisk_model_sources
obelisk_lib_sources += sqlite_sources

incdirs = include_directories(['.', 'include'])

lib = static_library('obelisk',
    obelisk_lib_sources,
    c_args : sqlite_args,
    include_directories: [incdirs, sqlite_include_directories],
    install : true
)

shared_library('obelisk',
    obelisk_lib_sources,
    c_args : sqlite_args,
    include_directories: incdirs,
    version : meson.project_version(),
    soversion : project_version_lib,
    install : true
)

libobelisk = declare_dependency(
    include_directories : incdirs,
    link_with : lib,
    sources : obelisk_lib_sources
)
