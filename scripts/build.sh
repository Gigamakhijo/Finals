#!/bin/bash

mkdir build bins

set -e

cmake -DCMAKE_BUILD_TYPE=Debug  -S . -B build
make -C build
