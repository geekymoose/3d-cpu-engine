#!/bin/bash

set -x
set -e
set -v

mkdir build || true
cd build

cmake -DCMAKE_BUILD_TYPE=${BUILD_TYPE} \
      -Dbuild_tests=ON \
      ..

make
make runAllTests
