#!/usr/bin/env python3
from collections import Counter

def solve(c):
  factors = []
  def add_factor(a):
    nonlocal c, factors
    c -= Counter(a)
    a = [str(x) for x in a]
    factors.append(a[0] if len(a) == 1 else '(' + '+'.join(a) + ')')

  while c[1] > 0 or c[2] > 0:
    if (c[1] == 2 and c[2] == 1) or c[1] == 0:
      add_factor([2])
    elif c[1] > 0 and c[2] > 0:
      add_factor([1,2])
    elif c[1] == 4 or c[1] == 2:
      add_factor([1,1])
    elif c[1] >= 3:
      add_factor([1,1,1])
    elif c[1] == 1:
      if sum(c.values()) > c[0]+c[1]:
        x = min(x for x in c if x > 1)
        add_factor([1,x])
      else:
        add_factor([1])
  for x, k in c.items():
    if x > 0:
      factors += [str(x)] * k
  res = '*'.join(factors) + '+0' * c[0]
  if res[0] == '+':
    res = res[1:]
  return res

input()
print(solve(Counter(map(int, input().split()))))
