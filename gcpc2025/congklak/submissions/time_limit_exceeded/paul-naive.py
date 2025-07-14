#!/usr/bin/env python3

def go(h, x):
  if h > 1:
    return x+1, h-1
  if x > 0:
    return 0, x+1
  return 1, 0

n, k = map(int, input().split())
a = list(map(int, input().split()))

while k > 0:
  h = 1
  for i in range(n):
    a[i], h = go(h, a[i])
    if h == 0:
      break
  k -= 1

print(*a)
