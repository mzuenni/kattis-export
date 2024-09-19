#!/usr/bin/env python3
# @EXPECTED_RESULTS@: TIME_LIMIT_EXCEEDED, RUN_TIME_ERROR
from functools import lru_cache

@lru_cache(maxsize=None)
def solve(a):
  if len(a) == 1:
    return str(a[0])
  res = '*'.join(str(x) for x in a)
  for mask in range(1 << len(a)):
    b, c = [], []
    for i, x in enumerate(a):
      if mask & 1 << i:
        b.append(x)
      else:
        c.append(x)
    b = tuple(b)
    c = tuple(c)
    if b and c:
      rb = solve(b)
      rc = solve(c)
      for op in '+*':
        cur = f'({rb}){op}({rc})'
        if eval(cur) > eval(res):
          res = cur
  return res

input()
a = tuple(map(int, input().split()))
print(solve(a))
