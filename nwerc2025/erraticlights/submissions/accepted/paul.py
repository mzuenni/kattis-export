#!/usr/bin/env python3
from collections import Counter
from functools import cache

n, k = int(input()), 3

@cache
def expected_steps(k, a):
  if len(a) == 1:
    return 0
  res = k
  a = list(a)
  a[0] -= 1
  for i in range(1, len(a)):
    a[i] += 1
    res += expected_steps(k, tuple(sorted(x for x in a if x > 0)))
    a[i] -= 1
  a[0] += 1
  res /= len(a) - 1
  return res

a = tuple(sorted(Counter(input()).values()))
print(expected_steps(k, a))
