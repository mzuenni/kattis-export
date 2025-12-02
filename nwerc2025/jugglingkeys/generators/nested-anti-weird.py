#!/usr/bin/env python3
import random
import sys

MAXT = 10**9

seed = int(sys.argv[1])
n = int(sys.argv[2])

random.seed(seed)

a = random.sample(range(1, MAXT), k=6*n)
a.sort()

intervals = []

for i in range(n):
	intervals.append((a[2*i], a[2*i+1]))

print(n,1,3*n-5)
print(2, 0, a[5*n-1]+1)
for i in range(2, n):
	print(i+1, a[i], a[2*n-1-i])
for i in range(2, n):
	print(i+1, a[2*n+i], a[4*n-1-i])
for i in range(2, n):
	print(i+1, a[4*n+i], a[6*n-1-i])

