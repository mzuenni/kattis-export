#!/usr/bin/env python3
import random
import sys

MAXT = 10**9

seed = int(sys.argv[1])
n = int(sys.argv[2])
k = int(sys.argv[3])

random.seed(seed)

intervals = []

taken = set()

for i in range(n):
	x = random.randint(n+3, MAXT-n-3)
	while x in taken or x+1 in taken:
		x = random.randint(n+3, MAXT-n-3)
	taken.add(x)
	taken.add(x+1)
	intervals.append((i, i, x-1))
	intervals.append((i, x, MAXT-n+i-1))

random.shuffle(intervals)

q = 2*n
print(n,k,q)
for i,x,y in intervals:
	print(i+1,x+1,y+1)

