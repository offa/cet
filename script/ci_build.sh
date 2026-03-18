#!/bin/bash

set -ex

BUILD_TYPE="Release"

pipx install ninja

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
    -s compiler.cppstd=20 \
    -s build_type=${BUILD_TYPE} \
    -c "tools.cmake.cmaketoolchain:generator=Ninja" \
    ..

cmake --preset conan-release ..
cmake --build . -j
cmake --build . --target unittest
