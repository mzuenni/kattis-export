#!/usr/bin/env python3

n, h = map(int, input().split())
l = 0

for _ in range(n):
  a = sorted(map(int, input().split()))
  if a[0] > h:
    print('impossible')
    break
  l += a[a[1] > h]
else:
  print(l)
