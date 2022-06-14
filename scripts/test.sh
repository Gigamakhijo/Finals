#!/bin/bash

source scripts/build.sh

cd build && ctest -V
