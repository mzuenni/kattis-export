#!/usr/bin/env python3
import math

n = int(input())
cranes = [tuple(map(int, input().split())) for _ in range(n)]

for i in range(n):
  x1, y1, h1 = cranes[i]
  r = h1
  for j in range(i):
    x2, y2, h2 = cranes[j]
    if h2 > h1:
      r = min(r, math.hypot(x2-x1, y2-y1))
  print(int(r))
