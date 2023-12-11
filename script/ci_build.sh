#!/bin/bash

set -ex

PIP_BIN="pip"
BUILD_TYPE="Release"

if ! command -v "${PIP_BIN}" &> /dev/null
then
    PIP_BIN="pip3"
fi

if [[ -z ${WINDIR+x} ]]
then
    apt-get update
    apt-get install -y python3-pip ninja-build
fi

${PIP_BIN} install -U conan
conan profile detect

if [[ "${CXX}" == clang* ]]
then
    export CXXFLAGS="-stdlib=libc++"
    sed -i 's/^compiler.libcxx=.*$/compiler.libcxx=libc++/g' ~/.conan2/profiles/default
elif [[ -n ${WINDIR+x} ]]
then
    export CC=cl
    export CXX=cl
fi

mkdir build && cd build

conan install \
    -of . \
    --build=missing \
    -s compiler.cppstd=17 \
    -s build_type=${BUILD_TYPE} \
    -c "tools.cmake.cmaketoolchain:generator=Ninja" \
    ..

cmake --preset conan-release ..
cmake --build . -j
cmake --build . --target unittest
