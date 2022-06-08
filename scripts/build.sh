#!/bin/bash

mkdir build dist

set -e

cmake -B`pwd`/build -S`pwd`
cd build 
make 
chmod +x encoder.out 
chmod +x decoder.out

mv encoder.out ../dist 
mv decoder.out ../dist
