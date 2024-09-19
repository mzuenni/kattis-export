#!/usr/bin/env python3

def bc(x):
  return bin(x).count('1')

a = [input() for _ in range(7)]
d, h = map(int, input().split())

res = 0
for mask in range(1 << 7):
  if bc(mask) < d:
    continue
  b = [sum(a[j][i] == '.' for j in range(7) if mask & (1 << j)) for i in range(24)]
  res = max(res, sum(sorted(b)[-h:]) / (h * bc(mask)))
print(res)
