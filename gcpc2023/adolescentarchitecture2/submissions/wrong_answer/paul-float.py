#!/usr/bin/env python3
from functools import *
from math import *

scale = [
  [1, sqrt(2), sqrt(3)],
  [1/2, 1, sqrt(6)-sqrt(2)],
  [1/sqrt(12), sqrt(12)-3, 1]
]

def fit(i, x, j, y):
  return x < y * scale[j][i]

def grundy(i, x):
  global max_steps
  if i == 0 and x == 1:
    return 2
  g = int(x * scale[i][2])
  while fit(2, g, i, x):
    g += 1
  while not fit(2, g, i, x):
    g -= 1
  return g

def inv_grundy(i, g):
  if i == 2:
    return g+1
  if i == 0 and g == 2:
    return 1
  x = int(g / scale[i][2])
  while fit(2, g, i, x):
    x -= 1
  while not fit(2, g, i, x):
    x += 1
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
    res += 0 < y and fit(j, y, i, x)
print(res)
