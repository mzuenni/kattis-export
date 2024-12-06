#!/usr/bin/env python3
import math
import random

random.seed(987)

n = int(input())

s, g, x = 0, 0, random.randint(1, n)
seen = dict()
while not 1 <= g <= n:
  seen[x] = s
  k = random.randint(1, n)
  print('?', k, x, flush=True)
  x = int(input())
  s += k
  if x in seen:
    g = math.gcd(g, s - seen[x])
  seen[x] = s

print('?', 1 + (-x-1) % g, x, flush=True)
print('!', x, input())
