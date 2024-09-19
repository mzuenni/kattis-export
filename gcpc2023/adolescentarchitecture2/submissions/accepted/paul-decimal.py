#!/usr/bin/env python3
from decimal import *
from functools import *

scale = [
  [Decimal(1), Decimal(2).sqrt(), Decimal(3).sqrt()],
  [Decimal(1/2), Decimal(1), Decimal(6).sqrt() - Decimal(2).sqrt()],
  [1/Decimal(12).sqrt(), Decimal(12).sqrt()-3, Decimal(1)]
]

def grundy(i, x):
  if i == 0 and x == 1:
    return 2
  g = x * scale[i][2]
  return int(g-1 if g == int(g) else g)

def inv_grundy(i, g):
  if i == 2:
    return g+1
  if i == 0 and g == 2:
    return 1
  x = int(g / scale[i][2] + 1)
  return x if grundy(i, x) == g else 0

n = int(input())
shapes = []
for _ in range(n):
  s, t = input().split()
  shapes.append(('cst'.index(s[0]), int(t)))

G = reduce(lambda g, h: g^h, (grundy(i, x) for i, x in shapes))

res = 0
for i, x in shapes:
  g = grundy(i, x)
  for j in range(3):
    y = inv_grundy(j, G ^ g)
    res += 0 < y < x * scale[i][j]
print(res)
