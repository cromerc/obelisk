conf_data = configuration_data()
conf_data.set('version', meson.project_version())
conf_data.set('so_version', project_version_lib)
configure_file(input : 'version.h.in',
    output : 'version.h',
    configuration : conf_data
)

obelisk_lib_sources = files(
)

sqlite3 = dependency('sqlite3')

library('obelisk',
    obelisk_lib_sources,
    dependencies : [sqlite3],
    version : meson.project_version(),
    soversion : project_version_lib,
    install : true
)
