#!/usr/bin/env python3
import sys, random, math

random.seed(int(sys.argv[1]))

# Generate a 2-layer star graph, with branching factor sqrt(n)

n = int(sys.argv[2])
m = int(sys.argv[3])

idxs = [i for i in range(1, n+1)]
random.shuffle(idxs)

sqrtn = int(math.sqrt(n))

print(n)

# First layer
for i in range(1, sqrtn):
    print(idxs[0], idxs[i], i)

# Second layer
for j in range(sqrtn, n):
    print(idxs[j], idxs[1 + j % sqrtn] ,j)

print(m)
connected = set()
for i in range(m):
    a = random.randrange(1+sqrtn, n)
    b = a
    while b == a or (a,b) in connected or (b,a) in connected:
        b = random.randrange(1+sqrtn, n)
    connected.add((a,b))
    print(idxs[a], idxs[b])
