#!/bin/bash

mkdir build bins

set -e

cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
make -C build
