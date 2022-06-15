#!/bin/bash

set -e

cd build

for i in {1..1000}
do
    echo $i번째 시뮬레이션
    ./encoder.out ../data/data.txt encoded_data
    ../data/adversary.out encoded_data 4 >> log.txt
    ./decoder.out encoded_data.modified decode.txt
    echo diff:
    diff decode.txt ../data/data.txt
done
