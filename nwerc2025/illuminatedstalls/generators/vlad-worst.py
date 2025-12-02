#!/usr/bin/env python3
import random

random.seed(987)

n = 200_000
k = 100_000
ys = random.sample(range(10**9 + 1), k)

print(1)
print(n)
for i, y in enumerate(ys):
  print(2*i, y, 2*i+1, y)
for i in range(n-k):
  print(2*k+i, 0, 2*k+i, 10**9)
