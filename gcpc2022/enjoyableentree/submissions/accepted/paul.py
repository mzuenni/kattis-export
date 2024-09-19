#!/usr/bin/env python3

n = min(100, int(input()))
a, b, c, d = 100, 0, 0, 100

for _ in range(n-1):
    a, b, c, d = c, d, (a+c)/2, (b+d)/2

print(a,b)
