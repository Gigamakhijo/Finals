#!/bin/bash

source scripts/build.sh

cd build && ctest

echo "original:"
cat ../data/data.txt

echo "encoded:"
./encoder.out ../data/data.txt encoded_data
cat encoded_data

echo "modified:"
../data/adversary.out encoded_data 4 >> log.txt
 cat encoded_data.modified

./decoder.out encoded_data.modified decode.txt
echo "decoded:"
cat decode.txt

echo "diff:"
diff ../data/data.txt decode.txt
