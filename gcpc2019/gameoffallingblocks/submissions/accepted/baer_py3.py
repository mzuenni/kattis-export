#!/bin/python3
import sys
ps = {"I": (1, 1), "J": (2, 3), "L": (2, 3), "O": (0, 2), "S":(1, 2), "T": (2, 3), "Z": (1, 2)}
left = 1
i = 0
while left <= 10:
	a=input()
	if left + ps[a][1] <= 11:
		print(ps[a][0], left)
		left += ps[a][1]
	else:
		print(0,(i%2) * 3 + 1)
		i += 1
	sys.stdout.flush()
input()
