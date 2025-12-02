#!/usr/bin/env python3
# @EXPECTED_RESULTS@: ACCEPTED, TIME_LIMIT_EXCEEDED
import random

random.seed(987)

coins = [a*b for a in [100, 10, 1] for b in [5, 2, 1]]

n = int(input())
for _ in range(10000):
  a = []
  r = n
  for x in coins:
    k = random.randint(0 if x > 1 else r, r//x)
    r -= k*x
    a += [x] * k
  dp = 1
  for x in a:
    dp |= dp << x
  if n%2 == 1 or dp & (1 << (n//2)) == 0:
    # print('unsplittable')
    print(len(a))
    print(*a)
    exit(0)
print('splittable')
