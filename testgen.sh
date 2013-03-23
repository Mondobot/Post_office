#!/bin/bash

N_TESTS=10

make

echo $N_TESTS
for i in $(seq 1 $N_TESTS)
do
    NAME="test"$i".in"
    N=$(($RANDOM%$(($i*$(($RANDOM%1163))))))


    echo $NAME
    echo $N

    ./test_gen $NAME $N
done
