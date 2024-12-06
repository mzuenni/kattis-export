#!/usr/bin/env python3

n, k = map(int, input().split())
name = input()
stride = pow(2, k, n)
pos = 0
for i in range(n):
    print(name[pos], end="")
    pos += stride
    pos -= n * (pos >= n)
print()
