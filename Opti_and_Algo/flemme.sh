#!/bin/bash
make 2> /dev/null > /dev/null
valgrind --tool=cachegrind --D1=4096,4,64 ./bin/distanceEdition tests/ba52_recent_omicron.fasta 0 4000 tests/wuhan_hu_1.fasta 0 4000 2> $1

rm -f cachegrind.out.*