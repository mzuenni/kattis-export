#!/usr/bin/env python3
import random
import sys

random.seed(int(sys.argv[1]))

n = int(sys.argv[2])
mul = eval(sys.argv[3]) if 3 < len(sys.argv) else 1
add = eval(sys.argv[4]) if 4 < len(sys.argv) else 0

a = [x+1 for x in range(n)]
b = [0-x for x in range(n)]

if "shuffle" in sys.argv[1:]:
	perm = list(range(n))
	random.shuffle(perm)
	a = [a[i] for i in perm]
	b = [b[i] for i in perm]

if "reverseB" in sys.argv[1:]:
	b.reverse()

if "shuffleB" in sys.argv[1:]:
	random.shuffle(b)

print(len(a))
for p in a+b:
	p = p*mul+add
	print(round(p.real), round(p.imag))
