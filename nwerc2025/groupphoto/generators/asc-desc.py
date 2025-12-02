#!/usr/bin/python3
import sys

l = int(sys.argv[1])
r = int(sys.argv[2])
inv = sys.argv[3] == 'inv'
n = l + r
print(n)

def num(k):
  if inv:
    return n - k + 1
  else:
    return k

ll = 0
rr = 0
p = list(range(n))
while ll + rr < n:
  if ll < l:
    p[ll] = num(ll + rr + 1)
    ll = ll + 1
  if rr < r:
    p[n - rr - 1] = num(ll + rr + 1)
    rr = rr + 1

print(*p)
