#!/usr/bin/env python3
import random
import sys

MAXT = 10**9

seed = int(sys.argv[1])
n = int(sys.argv[2])
k = int(sys.argv[3])
q = int(sys.argv[4])
out_weight = int(sys.argv[5])


random.seed(seed)

inside = set(range(n))
outside = set()

times = random.sample(range(1, MAXT+1), 2*q)
times.sort()
intervals = []
entered = [-1] * n

for i in range(2*q):
	if 2*q-i == len(outside):
		out_list = list(outside)
		j = i
		for x in out_list:
			intervals.append((x, entered[x], times[j]))
			j += 1
		break
	for _ in range(out_weight):
		x = random.randrange(0, n)
		if x in inside or len(inside) == 0:
			break
	if x in inside:
		inside.remove(x)
		outside.add(x)
		entered[x] = times[i]
	else:
		inside.add(x)
		outside.remove(x)
		intervals.append((x, entered[x], times[i]))

random.shuffle(intervals)

print(n,k,q)
for i,x,y in intervals:
	print(i+1,x+1,y+1)

