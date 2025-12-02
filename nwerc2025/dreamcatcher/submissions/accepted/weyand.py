#!/usr/bin/env python3
from math import gcd

n = int(input())
k = n//2
while gcd(k,n)>1:
    k-=1
print(k)
