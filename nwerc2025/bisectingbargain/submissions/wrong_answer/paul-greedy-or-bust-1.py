#!/usr/bin/env python3

n = int(input())
if (n // 1000) % 2 == 0 and all(c in '04' for c in str(n % 1000)):
  print('splittable')
else:
  res = []
  for c in [500, 200, 100, 50, 20, 10, 5, 2, 1]:
    res += [c] * (n//c)
    n %= c
  print(len(res))
  print(*res)
