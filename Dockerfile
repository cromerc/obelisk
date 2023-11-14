FROM ubuntu:22.04 AS build-prep
RUN apt update && apt upgrade -y
RUN apt install -y llvm clangd meson ninja-build pkg-config libsqlite3-dev doxygen graphviz wget unzip
WORKDIR /obelisk
COPY . .
RUN ./sqlite.sh

FROM build-prep AS build-machine
RUN meson --prefix=/usr build
RUN cd build && ninja -v

FROM build-machine AS build-machine-intermediate
RUN cd /obelisk/build/src/lib && rm -rf *.h *.p models

FROM scratch AS obelisk
COPY --from=build-machine-intermediate /obelisk/build/src /bin/
COPY --from=build-machine-intermediate /obelisk/build/src/lib /lib/
COPY --from=build-machine-intermediate /obelisk/build/doc/man /man/
COPY --from=build-machine-intermediate /obelisk/build/doc/html /doc/
ENTRYPOINT [ "/bin/obelisk" ]

FROM scratch AS binaries
COPY --from=obelisk /bin/obelisk /bin/
COPY --from=obelisk /lib /lib/
COPY --from=obelisk /man /man/
COPY --from=obelisk /doc /doc/
