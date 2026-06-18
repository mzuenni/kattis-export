#!/usr/bin/env python3
import itertools

n = int(input())
xs = [list(map(int, input().split())) for _ in range(2*n)]
gs = itertools.groupby(sorted([(c, l-r) for l, r, c in xs]), key=lambda x: x[0])

ys = []
for c, g in gs:
  g = sorted(g)
  m, k = len(g), len(g)//2
  ys += [y + c * ((i >= m-k) - (i < k)) for i, (_, y) in enumerate(g)]

print(sum(x[1] for x in xs) + sum(sorted(ys)[n:]))
