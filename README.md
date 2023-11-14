# Obelisk

The Obelisk project is a declarative language designed to help with the implementation of Artificial Intelligence using an easy to use logical programming language.

## Build requirements

 - Meson
 - Ninja
 - LLVM 14
 - sqlite 3 library and headers(in debian libsqlite3-dev)
 - C++ 17
 - C 17

## Build

### Normal build

```
./sqlite.sh
meson builddir
cd buildir
ninja
```

This process will generate the binary "obelisk", a shared library "libobelisk.so", and a static library "libobelisk.a".

The binary is used to compile and create obelisk knowledge bases and the the libraries can be linked against to consult the Obelisk knowledge base from any software that can link with the libraries.

### Build in docker image

```
docker build ./ --output=out
```

This will create a directory called out which will contain the binaries, libraries, and generated documentation.

## Install

```
ninja install
```

This will install the Obelisk cli and the Obelisk library globally. You can also copy the resulting shared and/or static library to a project to link against and use an Obelisk knowledge base.

## License

Obelisk is licensed under the [The 3-Clause BSD License](LICENSE).

## Authors

 - Christopher Cromer
 - Martín Araneda
