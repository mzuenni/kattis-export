#!/usr/bin/env python3

k = int(input().split()[1])
a = input()
m = sum(c == d for c, d in zip(a, 'R'+a))
print(max(k-m, 0))
