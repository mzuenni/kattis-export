#!/usr/bin/env python3
import random
import sys

random.seed(int(sys.argv[1]))

k = int(sys.argv[2])
dx = random.randint(1, 10)
dy = random.randint(1, 10)

a = []
b = []
for i in range(-k, k+1):
	a.append((-dy+i*dx, dx+i*dy))
	b.append((dy+i*dx, -dx+i*dy))
x = -random.randint(1, 100)
y = random.randint(1, 100)
sq = dx**2 + dy**2
r = (x*dy-y*dx)
x2 = round(x-2*r*dy/sq)
y2 = round(y+2*r*dx/sq)
a.append((x, y))
b.append((x2+random.randint(-1, 1), y2+random.randint(-1, 1)))

print(len(a))
for p in a+b:
	print(*p)
