#!/usr/bin/env python3
from functools import *

def fit(i, x, j, y):
  if i == j:
    return x < y
  elif j == 0 and i == 1:
    return x**2 < 2*y**2
  elif j == 0 and i == 2:
    return x**2 < 3*y**2
  elif j == 1 and i == 0:
    return 2*x < y
  elif j == 1 and i == 2:
    return 48*y**4 < (8*y**2 - x**2)**2 and x < 2*y
  elif j == 2 and i == 0:
    return 12*x**2 < y**2
  else:
    return x*(x+6*y) < 3*y**2

def grundy(i, x):
  if i == 0 and x == 1:
    return 2
  lo, hi = 0, 2*10**9
  while lo+1 < hi:
    md = (lo+hi) // 2
    if fit(2, md, i, x):
      lo = md
    else:
      hi = md
  return lo

def inv_grundy(i, g):
  if i == 2:
    return g+1
  if i == 0 and g == 2:
    return 1
  lo, hi = 0, 2*10**9
  while lo+1 < hi:
    md = (lo+hi) // 2
    if fit(2, g, i, md):
      hi = md
    else:
      lo = md
  return hi if grundy(i, hi) == g else 0

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
    res += 0 < y and fit(j, y, i, x)
print(res)
