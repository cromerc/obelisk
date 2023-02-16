conf_data = configuration_data()
conf_data.set('version', meson.project_version())
conf_data.set('so_version', project_version_lib)
configure_file(input : 'version.h.in',
    output : 'version.h',
    configuration : conf_data
)

obelisk_lib_sources = files(
    'obelisk.cpp'
)

sqlite3 = dependency('sqlite3')

incdirs = include_directories(['.', 'include'])
lib = library('obelisk',
    obelisk_lib_sources,
    include_directories: incdirs,
    dependencies : [sqlite3],
    version : meson.project_version(),
    soversion : project_version_lib,
    install : true
)

libobelisk = declare_dependency(
    include_directories : incdirs,
    link_with : lib,
    sources : obelisk_lib_sources
)
