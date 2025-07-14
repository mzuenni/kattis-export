#!/usr/bin/env python3

def go(h, x):
  if h > 1:
    return x+1, h-1
  if x > 0:
    return 0, x+1
  return 1, 0

n, k = map(int, input().split())
a = list(map(int, input().split()))
n += 99
a += [0] * 99

while k > 0:
  i = 0
  while 2*i < n and a[2*i] == 0 and 2**(i+1) < k:
    i += 1
  for j in range(i):
    a[2*j] = 1
    a[2*j+1] += 2**(i-j-1) - 1
  k -= 2**i - 1

  h = 1
  for i in range(n):
    a[i], h = go(h, a[i])
    if h == 0:
      break
  k -= 1

print(*a[:-99])
