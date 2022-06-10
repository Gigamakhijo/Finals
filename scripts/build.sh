#!/bin/bash

mkdir build bins

set -e

cmake -S . -B build
make -C build
