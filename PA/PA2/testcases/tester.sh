#!/bin/bash

read -p "enter steps: " num_steps
read -p "enter test cases: " test_num

mkdir -p testcase"$test_num"
# append i at the end of test cases
for i in $(seq 1 $num_steps)
do
    cat testcase"$test_num".txt > testcase"$test_num"/testcase"$test_num"_"$i".txt
    echo "\n"$i >> testcase"$test_num"/testcase"$test_num"_"$i".txt
done

cat testcase"$test_num"/testcase"$test_num"_"$num_steps".txt > testcase"$test_num"/output"$test_num".txt
for i in $(seq 1 $num_steps)
do
    cat testcase"$test_num"/testcase"$test_num"_"$i".txt | ../PA2.exe |  tail -n 15 >> testcase"$test_num"/output"$test_num".txt 
done

cat testcase"$test_num"/testcase"$test_num"_"$num_steps".txt | ../PA2 | sed -e "s/$/\r/"  > testcase"$test_num"/output"$test_num"_my.txt

diff testcase"$test_num"/output"$test_num".txt testcase"$test_num"/output"$test_num"_my.txt