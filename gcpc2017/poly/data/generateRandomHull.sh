#!/bin/bash

g++ -O2 random.cpp -o gen
g++ -O2 maze.cpp -o maze
g++ -O2 ../submissions/accepted/gregor.cpp -o sol

echo "101 100" | ./gen | tee secret/71-randomHull.in | ./sol | tee secret/71-randomHull.ans
echo "102 100" | ./gen | tee secret/72-randomHull.in | ./sol | tee secret/72-randomHull.ans
echo "103 100" | ./gen | tee secret/73-randomHull.in | ./sol | tee secret/73-randomHull.ans
echo "104 100" | ./gen | tee secret/74-randomHull.in | ./sol | tee secret/74-randomHull.ans

echo "101 100 1 0" | ./maze | tee secret/81-maze.in | ./sol | tee secret/81-maze.ans
echo "102 100 1 0" | ./maze | tee secret/82-maze.in | ./sol | tee secret/82-maze.ans
echo "103 100 2 0" | ./maze | tee secret/83-maze.in | ./sol | tee secret/83-maze.ans
echo "104 100 2 0" | ./maze | tee secret/84-maze.in | ./sol | tee secret/84-maze.ans
echo "105 100 3 0" | ./maze | tee secret/85-maze.in | ./sol | tee secret/85-maze.ans
echo "106 100 3 0" | ./maze | tee secret/86-maze.in | ./sol | tee secret/86-maze.ans
echo "107 100 4 0" | ./maze | tee secret/87-maze.in | ./sol | tee secret/87-maze.ans
echo "108 100 4 0" | ./maze | tee secret/88-maze.in | ./sol | tee secret/88-maze.ans

echo "111 100 1 1" | ./maze | tee secret/91-maze-rot.in | ./sol | tee secret/91-maze-rot.ans
echo "112 100 1 1" | ./maze | tee secret/92-maze-rot.in | ./sol | tee secret/92-maze-rot.ans
echo "113 100 2 1" | ./maze | tee secret/93-maze-rot.in | ./sol | tee secret/93-maze-rot.ans
echo "114 100 2 1" | ./maze | tee secret/94-maze-rot.in | ./sol | tee secret/94-maze-rot.ans
echo "115 100 3 1" | ./maze | tee secret/95-maze-rot.in | ./sol | tee secret/95-maze-rot.ans
echo "116 100 3 1" | ./maze | tee secret/96-maze-rot.in | ./sol | tee secret/96-maze-rot.ans
echo "117 100 4 1" | ./maze | tee secret/97-maze-rot.in | ./sol | tee secret/97-maze-rot.ans
echo "118 100 4 1" | ./maze | tee secret/98-maze-rot.in | ./sol | tee secret/98-maze-rot.ans

rm gen sol maze
