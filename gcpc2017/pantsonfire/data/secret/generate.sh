#!/bin/bash

g++ -O2 generator.cpp -o gen
g++ -O2 ../../submissions/accepted/gregor.cpp -o sol

# seed -- number of statements -- number of countries
echo "101 200 50" | ./gen | tee 10-random-200-50.in | ./sol | tee 10-random-200-50.ans
echo "102 200 50" | ./gen | tee 11-random-200-50.in | ./sol | tee 11-random-200-50.ans
echo "103 200 50" | ./gen | tee 12-random-200-50.in | ./sol | tee 12-random-200-50.ans

echo "104 200 25" | ./gen | tee 13-random-200-25.in | ./sol | tee 13-random-200-25.ans
echo "105 200 25" | ./gen | tee 14-random-200-25.in | ./sol | tee 14-random-200-25.ans
echo "106 200 25" | ./gen | tee 15-random-200-25.in | ./sol | tee 15-random-200-25.ans

echo "107 200 100" | ./gen | tee 16-random-200-100.in | ./sol | tee 16-random-200-100.ans
echo "108 200 100" | ./gen | tee 17-random-200-100.in | ./sol | tee 17-random-200-100.ans
echo "109 200 100" | ./gen | tee 18-random-200-100.in | ./sol | tee 18-random-200-100.ans

echo "107 200 193" | ./gen | tee 19-random-200-193.in | ./sol | tee 19-random-200-193.ans
echo "108 200 193" | ./gen | tee 20-random-200-193.in | ./sol | tee 20-random-200-193.ans
echo "109 200 193" | ./gen | tee 21-random-200-193.in | ./sol | tee 21-random-200-193.ans

rm gen sol
