#!/usr/bin/env python3
import math

n = int(input())
ps = [complex(*map(int, input().split())) for _ in range(n)]
ps += ps

def dot(p, q):
  return (p.conjugate() * q).real

def cross(p, q):
  return (p.conjugate() * q).imag

res = 0
for i in range(2, n+2):
  a, b, c, d, e = ps[i-2:i+3]
  u, v, w = b-a, d-b, e-d
  if cross(u, v) == cross(v, w) == 0:
    continue
  #elif dot(u, v) > 0 and dot(v, w) > 0 and dot(u, w) > 0:
    #z = a + cross(d-a, w) / cross(u, w) * u
  elif dot(u, v) >= cross(u, v):
    z = b + dot(u, v) / dot(u, u) * u
  elif -dot(u, v) >= cross(u, v):
    z = b + cross(u, v) / dot(u, u) * u*1j
  elif dot(v, w) >= cross(v, w):
    z = d - dot(v, w) / dot(w, w) * w
  elif -dot(v, w) >= cross(v, w):
    z = d + cross(v, w) / dot(w, w) * w*1j
  else:
    z = b + v * (0.5-0.5j)
  res = max(res, abs(z-b) + abs(d-z) - abs(c-b) - abs(d-c))
print(res)
