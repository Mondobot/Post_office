#!/bin/bash

# Se ruleza asa:
# sh test.sh <nume_executabil> <nr_de_teste>

# numele executabilului (main / tema1 / a.out etc.)
EXEC=$1
# numarul de teste
N_TESTS=$2

# Se ruleaza executabilul si se genereaza fisierele de output
# test1.out, test2.out etc.
for i in $(seq 1 $N_TESTS)
do
    ./$EXEC "test"$i".in" > "test"$i".out"
done


