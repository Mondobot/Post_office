#!/bin/bash

EXEC=$1
N_TESTS=$2

for i in $(seq 1 $N_TESTS)
do
    ./$EXEC "test"$i".in" > "test"$i".out"
done


