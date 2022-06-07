#!/bin/bash

mkdir build bins
cmake -B`pwd`/build -S`pwd`
cd build && make && mv encoder.out ../bins && mv decoder.out ../bins
