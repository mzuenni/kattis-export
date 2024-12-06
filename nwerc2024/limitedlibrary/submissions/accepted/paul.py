#!/usr/bin/env python3

m, n, u, v = map(int, input().split())
a = sorted(map(int, input().split()))
b = sorted(map(int, input().split()))

def check(k):
  i = 0
  use = [0] * m
  for x in b:
    while i < m and (x > a[i] or use[i] >= (v if i < k else u)):
      i += 1
    if i == m:
      return False
    use[i] += 1
  return True

lo, hi = -1, m+1
while hi-lo > 1:
  md = (lo + hi) // 2
  if check(md):
    lo = md
  else:
    hi = md

print(lo if lo >= 0 else 'impossible')
