#!/bin/bash

g++ -O2 ../submissions/accepted/gregor.cpp -o sol


echo 10 1000 100 1000 1 | ./a.out | tee ../data/secret/20-random.in | ./sol | tee ../data/secret/20-random.ans
echo 11 1000 100 1000 1 | ./a.out | tee ../data/secret/21-random.in | ./sol | tee ../data/secret/21-random.ans
echo 12 1000 100 1000 1 | ./a.out | tee ../data/secret/22-random.in | ./sol | tee ../data/secret/22-random.ans
echo 13 1000 100 1000 1 | ./a.out | tee ../data/secret/23-random.in | ./sol | tee ../data/secret/23-random.ans
echo 14 1000 100 1000 1 | ./a.out | tee ../data/secret/24-random.in | ./sol | tee ../data/secret/24-random.ans

echo 15 100 30 100 2 | ./a.out | tee ../data/secret/25-random.in | ./sol | tee ../data/secret/25-random.ans
echo 16 100 30 100 3 | ./a.out | tee ../data/secret/26-random.in | ./sol | tee ../data/secret/26-random.ans
echo 17 100 30 100 4 | ./a.out | tee ../data/secret/27-random.in | ./sol | tee ../data/secret/27-random.ans


echo 10 30 10 10 10 | ./a.out | tee ../data/secret/30-random-trap.in | ./sol | tee ../data/secret/30-random-trap.ans
echo 11 20 10 10 11 | ./a.out | tee ../data/secret/31-random-trap.in | ./sol | tee ../data/secret/31-random-trap.ans


rm sol
