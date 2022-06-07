#!/bin/bash

mkdir build bins

set -e

cmake -B`pwd`/build -S`pwd`
cd build 
make 
chmod +x encoder.out 
chmod +x decoder.out

mv encoder.out ../bins 
mv decoder.out ../bins
