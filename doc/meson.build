cdata.set('TOP_SRCDIR', meson.source_root())
cdata.set('TOP_BUILDDIR', meson.build_root())

doxyfile = configure_file(input: 'doxygen.conf.in',
    output: 'doxygen.conf',
    configuration: cdata,
    install: false
)

datadir = join_paths(get_option('datadir'), 'doc', 'obelisk')

html_target = custom_target('obelisk-docs',
    input: doxyfile,
    output: 'html',
    command: [doxygen, doxyfile],
    install: true,
    install_dir: datadir
)
