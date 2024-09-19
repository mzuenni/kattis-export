#!/usr/bin/env python3
from decimal import *

n = int(input())
prices = []
for _ in range(n):
    x,y,z = input().split(' ')
    prices.append((Decimal(x),int(y),int(z)))

prices = sorted(prices)

tb = sum(a[1] for a in prices)
ts = 0

best = (0,0)

for p,b,s in prices:
    ts += s
    best = max(best, (p * min(ts,tb), p))
    tb -= b

if best[0] > 0:
    print(best[1],best[0])
else:
    print('impossible')

