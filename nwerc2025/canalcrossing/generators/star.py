#!/usr/bin/env python3
import sys, random

random.seed(int(sys.argv[1]))

n = int(sys.argv[2])
m = int(sys.argv[3])

idxs = [i for i in range(1, n+1)]
random.shuffle(idxs)

print(n)
for i in range(1,n):
    print(idxs[0], idxs[i], i)

print(m)
connected = set()
for i in range(m):
    a = random.randrange(1, n)
    b = a
    while b == a or (a,b) in connected or (b,a) in connected:
        b = random.randrange(1, n)
    connected.add((a,b))
    print(idxs[a], idxs[b])
