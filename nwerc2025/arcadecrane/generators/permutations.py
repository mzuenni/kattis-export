#!/usr/bin/env python3
import random
import sys

# Append a bunch of small permutations together

s = int(sys.argv[1])
random.seed(s)

n = 0
a = []
while True:
  k = random.randint(1, 8)
  if n+k > 1000:
    break
  p = list(range(n+1, n+k+1))
  random.shuffle(p)
  n += k
  a += p

print(n)
print(*a)
