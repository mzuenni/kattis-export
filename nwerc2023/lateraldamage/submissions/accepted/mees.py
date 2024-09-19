#!/usr/bin/python3
import sys

n, k = [int(x) for x in input().split()]

sink_ct = 0

def get(x, y):
    global sink_ct
    x += 1
    y += 1
    print(x, y)
    sys.stdout.flush()
    res = input()
    if res == "sunk":
        sink_ct += 1
        if sink_ct == k:
            sys.exit()
    return res

hits = set()
for d in range(4, 210, 5):
    for i in range(d+1):
        j = d - i
        if 0 <= i < n and 0 <= j < n:
            res = get(i, j)
            if res == "hit":
                hits.add((i, j))

for i, j in hits:
    for d in range(1, 5):
        for ni, nj in [(i, j + d), (i, j - d), (i + d, j), (i - d, j)]:
            if 0 <= ni < n and 0 <= nj < n:
                get(ni, nj)
