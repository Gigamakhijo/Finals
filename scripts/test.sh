#!/bin/bash

source scripts/build.sh

cd build

echo "original:"
cat ../data/data.txt

echo "encoded:"
./encoder.out ../data/data.txt
cat encoded_data

echo "modified:"
../data/adversary.out encoded_data 4 >> log.txt
 cat encoded_data.modified

./decoder.out encoded_data.modified
echo "decoded:"
cat decode.txt

echo "diff:"
diff ../data/data.txt decode.txt
