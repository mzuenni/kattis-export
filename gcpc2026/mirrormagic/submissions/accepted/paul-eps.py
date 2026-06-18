#!/usr/bin/env python3
import cmath

def fail():
  print('impossible')
  exit(0)

n = int(input())
a = [tuple(map(int, input().split())) for _ in range(2*n)]

c = sum(complex(*p) for p in a[:n]) / n
d = sum(complex(*p) for p in a[n:]) / n
if c == d:
  fail()

m, v = (c+d) / 2, 1j*(d-c) / abs(d-c)

s, t = set(a[n:]), set()
for i in range(n):
  p = complex(*a[i])
  q = p - 2j * ((p-m) * v.conjugate()).imag * v
  t.add(((p-m) * v.conjugate()).imag < 0)
  x, y = q.real, q.imag
  x, y = round(q.real), round(q.imag)
  if abs(q - complex(x, y)) > 1e-9 or (x, y) not in s:
    fail()

if len(t) > 1:
  fail()

print('possible')
