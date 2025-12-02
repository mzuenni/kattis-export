#!/usr/bin/env python3

n = int(input())
tups = [list(map(int, input().split())) for _ in range(n)]
sa = sum(t[0] for t in tups)
sb = sum(t[1] for t in tups)

if sa < sb:
    print("impossible")
    exit(0)

for i in range(n):
    a, b = tups[i]
    if sb - (sa - a) <= b:
        print(i + 1)
        exit(0)
