#!/usr/bin/env python3
from math import gcd, sqrt

a, b = map(int, input().split())
g = gcd(a-1,b-1)

res = 1
for x in range(1,g):
    y = round(sqrt(g*g-x*x))
    if x*x + y*y == g*g:
        res += 1

print(res if a == b else 2*res)
