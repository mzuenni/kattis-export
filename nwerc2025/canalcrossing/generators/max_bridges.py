#!/usr/bin/env python3

maxn = 100000
maxm = 500000
maxw = 1000000

# Maximal number of bridges connected single nodes
print(maxn)
for i in range(1, maxn):
    print(f"{i} {i+1} {maxw}")

# Connect as many bridges to the first few nodes as possible
start = 1
m = maxm
print(maxm)
while m > 0:
    c = min(m, maxn - start - 1)
    m -= c
    for i in range(start + 2, start + c + 2):
        print(f"{start} {i}")
    start += 1
