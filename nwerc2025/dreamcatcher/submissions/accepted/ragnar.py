#!/usr/bin/env python3
import math

n = int(input())
k = n//2
while math.gcd(n, k) != 1:
    k -= 1
print(k)
