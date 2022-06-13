#!/bin/bash



for i in {1..1000}
do
    echo $i번째 시뮬레이션
    cd build
    ./encoder.out ../data/data.txt
    ./../data/adversary.out encoded_data 4 >> log.txt
    ./decoder.out encoded_data.modified
    echo cmp결과
    cmp -l decode.txt ../data/data.txt
    cd ..
done