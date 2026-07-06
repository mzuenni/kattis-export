#!/usr/bin/env python3

import sys

sys.setrecursionlimit(5*10**5)

n = int(input())
es = [[] for _ in range(n)]
for _ in range(n - 1):
    a, b, w = map(int, input().split())
    a -= 1
    b -= 1
    es[a].append((b, w))
    es[b].append((a, w))
m = int(input())
counts = [0] * n
for _ in range(m):
    a, b = map(int, input().split())
    counts[a - 1] += 1
    counts[b - 1] += 1

ans = 0


def dfs(v, p, w):
    c = counts[v]
    for u, wu in es[v]:
        if u == p:
            continue
        c += dfs(u, v, wu)
    if c % 2 == 1:
        global ans
        ans += w
    return c


dfs(0, -1, 0)
print(ans)
