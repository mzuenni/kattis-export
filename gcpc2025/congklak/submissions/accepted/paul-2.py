#!/usr/bin/env python3

def go(h, x):
  if h > 1:
    return x+1, h-1
  if x > 0:
    return 0, x+1
  return 1, 0

n, k = map(int, input().split())
a = list(map(int, input().split()))

for i in range(0, n, 2):
  while k > 0 and (a[i] > 1 or k%2 != 0):
    h = 1
    for j in range(i, n):
      a[j], h = go(h, a[j])
      if h == 0:
        break
    k -= 1
  k //= 2
  if i+1 < n:
    a[i+1] += k

print(*a)
