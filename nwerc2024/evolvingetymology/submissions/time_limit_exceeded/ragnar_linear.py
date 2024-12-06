#!/usr/bin/env python3

n, k = map(int, input().split())
name = input()
stride = 1

for _ in range(k):
    stride *= 2
    stride -= n * (stride >= n)
pos = 0
for i in range(n):
    print(name[pos], end="")
    pos += stride
    pos -= n * (pos >= n)
print()
