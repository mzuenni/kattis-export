#!/usr/bin/env python3

n = int(input())
a = [tuple(map(int, input().split())) for _ in range(n)]

sx, sy = sum(x for x, _ in a), sum(y for _, y in a)

tx, ty = 0, 0
total, area = 0, 0
for i, (x, y) in enumerate(a):
  total += (i*x - tx) * (sy - ty - (n-i)*y) - (i*y - ty) * (sx - tx - (n-i)*x)
  tx += x
  ty += y
  area -= x * a[i-1][1] - y * a[i-1][0]
print(total/area)
