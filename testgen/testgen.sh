#!/bin/bash

# numarul de teste de generat
N_TESTS=10

make

echo $N_TESTS
for i in $(seq 1 $N_TESTS)
do
    # numele e de forma testX.in (X in [0..N_TESTS])
    NAME="test"$i".in"

    # N = rand() % (i * (rand() % 1163))
    # !!! De modificat constanta 1163 !!!
    N=$(($RANDOM%$(($i*$(($RANDOM%1163))))))

    echo $NAME
    echo $N

    # se genereaza testele, fiecare avand N ghisee
    ./test_gen $NAME $N
done
