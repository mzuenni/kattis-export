#!/usr/bin/env python3
import itertools
import random

random.seed(987)

coins = [a*b for a in [100, 10, 1] for b in [5, 2, 1]]

n = int(input())
for perm in itertools.permutations(coins):
  a = []
  r = n
  for x in perm:
    a += [x] * (r//x)
    r %= x
  dp = 1
  for x in a:
    dp |= dp << x
  if n%2 == 1 or dp & (1 << (n//2)) == 0:
    # print('unsplittable')
    print(len(a))
    print(*a)
    exit(0)
print('splittable')
