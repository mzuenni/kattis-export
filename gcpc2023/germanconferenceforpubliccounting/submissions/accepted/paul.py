#!/usr/bin/env python3

s = input()
n, k = int(s), len(s)
r = int('1' * k)
print(10*(k-1) + n//r + (n < 10))
