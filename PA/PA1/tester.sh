#!/usr/bin/env bash
for i in {1..22}
do
echo "Running test $i"
echo "---------------"
./pa1 $i | diff ../expected/pre/test$i.txt -
done
echo "Done" 