#!/usr/bin/env python3
import random

random.seed(987)

coins = [a*b for a in [1, 2, 5] for b in [1, 10, 100]]

n = int(input())
for _ in range(10000):
  a = []
  r = n
  while r > 0:
    x = random.choice(coins)
    if x <= r:
      r -= x
      a.append(x)
  dp = 1
  for x in a:
    dp |= dp << x
  if n%2 == 1 or dp & (1 << (n//2)) == 0:
    # print('unsplittable')
    print(len(a))
    print(*a)
    exit(0)
print('splittable')
