#!/bin/python2
import heapq

w, p = map(int,raw_input().split(" "))

wins = []
for _ in range(w):
	k = list(map(int, raw_input().split(" ")))
	others = k[1:]
	for i in range(len(others)):
		others[i] = -others[i]
	heapq.heapify(others)
	b = 0
	while k[0] <= -others[0]:
		k[0] += 1
		b += 1
		heapq.heapreplace(others, others[0] + 1) # negative value
	wins += [b]
print sum(list(sorted(wins))[:w/2+1])
