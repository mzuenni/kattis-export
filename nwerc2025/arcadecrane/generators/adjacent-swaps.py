#!/usr/bin/env python3
import random
import sys

# Start with a sorted sequence and perform k random adjacent swaps

n, k, s = map(int, sys.argv[1:])
random.seed(s)

a = list(range(1, n+1))
for _ in range(k):
  i = random.randrange(n-1)
  a[i], a[i+1] = a[i+1], a[i]

print(n)
print(*a)
