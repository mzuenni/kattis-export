#!/usr/bin/env python3
import functools

def cross(a, b):
  return (a.conjugate() * b).imag

n = int(input())
a = [complex(*map(int, input().split())) for _ in range(n)]

c = (a[0] + a[n//2]) / 2
a = [p-c for p in a]

depth = 0
events = []
for i in range(n):
  p, q, r = a[i-2], a[i-1], a[i]
  if (cross(p, q) > 0) != (cross(q, r) > 0):
    events.append((q, (-2)**(cross(p-q, r-q) > 0) * (-1)**(cross(p, q) > 0)))
  depth += (p.real < 0) != (q.real < 0) and (p.real < 0) == (cross(p, q) < 0)
depth = (depth+1) // 2

def left(c):
  return c.real < 0 or (c.real == 0 and c.imag < 0)

def compare(c, d):
  p, i = c
  q, j = d
  if left(p) != left(q):
    return left(q)-left(p)
  if cross(q, p) != 0:
    return cross(q, p)
  return i-j

events.sort(key=functools.cmp_to_key(compare))

if not events:
  u, v = c, c+1
else:
  p = 1j
  for q, j in events:
    if depth == 1:
      u, v = c+p+q, c-p-q
      break
    depth += 1 if j in [1, -2] else -1
    p = q
  else:
    print('impossible')
    exit(0)

def frac(x):
  return str(int(2*x)) + '/2'

print(frac(u.real), frac(u.imag), frac(v.real), frac(v.imag))
