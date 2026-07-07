#!/usr/bin/env python3

n, a = list(map(int, input().split()))
ai = sorted([int(input()) for i in range(n)])

s = 0
for i in range(n):
	if s + ai[i] > a:
		break
	s += ai[i]

if s + i * 10 == a:
	print(a-s)
else:
	print("impossible")
