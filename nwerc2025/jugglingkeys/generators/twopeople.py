#!/usr/bin/env python3
import random
import sys

MAXT = 10**9

# Possible case n=2 and k=1
# There are two types of blocks of intervals:
# ([][][]) 
# [(][][][]) 
   

seed = int(sys.argv[1])
q = int(sys.argv[2])
blocks = int(sys.argv[3])

n = 2
k = 1

random.seed(seed)

intervals = []

times = random.sample(range(MAXT), 2*q)
times.sort()

bi = [0]
if blocks > 1:
	bi += list(random.sample(range(1, q), blocks-1))
bi.sort()

for i in range(len(bi)):
	nxt = q
	if i < len(bi)-1:
		nxt = bi[i+1]
	
	ti = 2*bi[i]
	
	block_type = 0
	if nxt-bi[i] > 1:
		block_type = random.randint(0,1)

	person = [0, 1]
	if random.randint(0, 1) == 1:
		person = [1, 0]

	tlast = 2*nxt-1

	if block_type == 0:
		intervals.append((person[0], times[ti], times[tlast]))
		for tj in range(ti+1,tlast,2):
			intervals.append((person[1], times[tj], times[tj+1]))
	else:
		intervals.append((person[0], times[ti], times[ti+2]))
		intervals.append((person[1], times[ti+1], times[tlast]))
		for tj in range(ti+3,tlast,2):
			intervals.append((person[0], times[tj], times[tj+1]))


#random.shuffle(intervals)

print(n,k,q)
for i,x,y in intervals:
	print(i+1,x+1,y+1)

