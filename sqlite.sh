#!/bin/bash

VERSION=sqlite-amalgamation-3410000

pushd sqlite
wget https://sqlite.org/2023/${VERSION}.zip
unzip ${VERSION}.zip
cp ${VERSION}/sqlite3.c .
cp ${VERSION}/sqlite3.h .
rm -rf ${VERSION} ${VERSION}.zip
popd
