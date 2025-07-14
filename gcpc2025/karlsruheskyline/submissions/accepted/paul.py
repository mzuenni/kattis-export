#!/usr/bin/env python3

def solve(n, a, b):
  assert a+b <= n+1 and max(a, b) > 1
  if a == 1:
    return [n] + list(range(1, n-b+1)) + list(range(n-1, n-b, -1))
  return list(range(n-a-b+2, n-b+1)) + list(range(1, n-a-b+2)) + list(range(n, n-b, -1))

try:
  h = solve(*map(int, input().split()))
  print('yes')
  print(*h)
except:
  print('no')
