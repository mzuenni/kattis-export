#!/usr/bin/env python3

a = set(tuple(map(int, input().split())) for _ in range(5))

res = 0
for _ in range(7):
  if len(a) > 1:
    v = sorted(p[0] for p in a)
    if v[0] < v[1]:
      res += v[1]-v[0]
      a = set((max(x, v[1]), y) for x, y in a)
    a = set((-y, x) for x, y in a)

v = sorted(set(p[0] for p in a))
w = sorted(set(p[1] for p in a))
dx = v[-1] - v[0]
dy = w[-1] - w[0]
res += 2 * (dx + dy)
if any(x not in [v[0], v[-1]] and y not in [w[0], w[-1]] for x, y in a):
  res += min(dx, dy)
print(res)
