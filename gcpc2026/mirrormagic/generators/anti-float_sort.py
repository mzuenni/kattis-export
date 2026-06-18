#!/usr/bin/env python3
import random
import sys

random.seed(int(sys.argv[1]))

k = int(sys.argv[2])

oo = int(1e6) - random.randint(0, 10000)

a = []
b = []
for i in range(k - 1):
    a.append((-oo, oo - i * int(9)))
    b.append((oo - i * int(9), -oo))
a.append((1 - oo, oo))
b.append((oo, 1 - oo))

if random.randint(0, 1) > 0:
    a, b = b, a
if random.randint(0, 1) > 0:
    a = [ (y,x) for (x,y) in a ]
    b = [ (y,x) for (x,y) in b ]

print(len(a))
for p in a+b:
	print(*p)
