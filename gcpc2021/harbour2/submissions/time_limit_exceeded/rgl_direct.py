#!/usr/bin/env python3

n,u,v = map(int,input().split())
u = [-1] + list(map(int, input().split()))
v = [-1] + list(map(int, input().split()))
res = 0

def is_zero_on_top():
  return len(u) > 0 and u[-1] == 0 or len(v) > 0 and v[-1] == 0

res = int(0 in (u[-1], v[-1]))
for i in range(1, n+1):
  if i in u: u, v = v, u
  x = v.index(i)
  u += v[:x:-1]
  v = v[:x]
  res += int(0 in (u[-1], v[-1]))

print(res)
