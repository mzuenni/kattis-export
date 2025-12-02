#!/usr/bin/env python3
# @EXPECTED_RESULTS@: ACCEPTED, TIME_LIMIT_EXCEEDED
import itertools

coins = [a*b for a in [100, 10, 1] for b in [5, 2, 1]]

n = int(input())
for perm in itertools.permutations(coins):
  a = []
  r = n
  for x in perm:
    a.append((r//x, x))
    r %= x
  dp = 1
  for (k, x) in a:
    dp *= ((1 << ((k+1)*x)) - 1) // ((1 << x) - 1)
  if n%2 == 1 or dp & (1 << (n//2)) == 0:
    # print('unsplittable')
    a = [x for k, x in a for _ in range(k)]
    print(len(a))
    print(*a)
    exit(0)
print('splittable')
