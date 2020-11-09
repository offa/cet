#!/bin/bash

set -ex

PIP_BIN="pip"

if ! command -v "${PIP_BIN}" &> /dev/null
then
    PIP_BIN="pip3"
fi

if [[ -z ${WINDIR+x} ]]
then
    apt-get install -y python3-pip ninja-build
fi

${PIP_BIN} install -U conan
conan profile new default --detect

if [[ "${CXX}" == clang* ]]
then
    export CXXFLAGS="-stdlib=libc++"
    conan profile update settings.compiler.libcxx=libc++ default
elif [[ -n ${WINDIR+x} ]]
then
    export CC=cl
    export CXX=cl
else
    conan profile update settings.compiler.libcxx=libstdc++11 default
fi

mkdir build && cd build

conan install \
    -g cmake_find_package \
    -g cmake_paths \
    --build=missing \
    ..

cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_TOOLCHAIN_FILE=./conan_paths.cmake -G Ninja ..
cmake --build . -j
cmake --build . --target unittest
