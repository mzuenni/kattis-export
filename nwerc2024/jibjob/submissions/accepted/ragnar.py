#!/usr/bin/env python3

n = int(input())
cs = [list(map(int, input().split())) for _ in range(n)]


def isqrt(x):
    s = int(x**0.5) - 1
    while (s + 1) * (s + 1) <= x:
        s += 1
    return s


for i in range(n):
    l = cs[i][2]
    for j in range(n):
        if cs[j][2] <= cs[i][2]:
            continue
        l = min(l, isqrt((cs[j][0] - cs[i][0]) ** 2 + (cs[j][1] - cs[i][1]) ** 2))
    print(l)
