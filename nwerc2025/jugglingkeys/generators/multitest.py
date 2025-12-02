#!/usr/bin/env python3
import random
import sys

MAXT = 10**9

def gen_tc(n,q):
	# Random testcase in the form of list a of length 2q containing an even number of all people
	f = [1] * n
	for _ in range(q-n):
		f[random.randrange(n)] += 1
	ind = []
	for i in range(n):
		ind += [i]*(2*f[i])
	random.shuffle(ind)
	return ind


def validate(n,k,ind):
	events = []
	q = len(ind) // 2
	ans = ['0'] * q

	ix = 0
	interval_index = [-1] * n
	for t in range(len(ind)):
		i = ind[t]
		if interval_index[i] == -1:
			interval_index[i] = ix
			ix += 1
			events.append((t, interval_index[i], 1))
		else:
			events.append((t, interval_index[i], -1))
			interval_index[i] = -1

	events.sort()

	gone = 0

	for i in range(len(events)):
		t, i, d = events[i]
		if gone == n and d == -1:
			ans[i] = '1'
		gone += d

	keys = k

	for i in range(len(events)):
		t, i, d = events[i]
		d *= int(ans[i])
		keys -= d
		if keys < 0:
			return False
	return True

   
seed = int(sys.argv[1])
n = int(sys.argv[2])
k = int(sys.argv[3])
q = int(sys.argv[4])
b = int(sys.argv[5])

assert b >= n

random.seed(seed)

intervals = []

index = []

for _ in range(q // b):
	ind = gen_tc(n,b)
	its = 0
	lim = 1000
	while its < lim:
		if not validate(n,k,ind):
			ind = gen_tc(n,b)
		else:
			break
		its += 1
	if its == lim:
		break
	index += ind

times = random.sample(range(MAXT), 2*q)
times.sort()

last_time = [-1] * n
for t in range(len(index)):
	i = index[t]
	if last_time[i] == -1:
		last_time[i] = t
	else:
		intervals.append((i, times[last_time[i]], times[t]))
		last_time[i] = -1


print(n,k,len(intervals))
for i,x,y in intervals:
	print(i+1,x+1,y+1)

