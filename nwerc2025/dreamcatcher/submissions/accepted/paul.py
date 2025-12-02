#!/usr/bin/env python3
from math import *

n = int(input())
res = (0, 0)
for k in range(n//2, max(n//2-100, 0), -1):
  res = max(res, (n / gcd(n, k) * 2 * sin(pi * k/n), k))
print(res[1])
