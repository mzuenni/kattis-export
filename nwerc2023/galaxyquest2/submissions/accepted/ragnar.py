#!/usr/bin/env python3
import heapq
from math import dist

n, m, Q = map(int, input().split())
ps = [tuple(map(int, input().split())) for _ in range(n)]
g = [[] for _ in range(n)]
for _ in range(m):
    u, v = map(int, input().split())
    u -= 1
    v -= 1
    g[u].append(v)
    g[v].append(u)

# Dijkstra to compute D=sum(sqrt(dist)) to all points
d = [float("inf")] * n
d[0] = 0
q = [(0, 0)]
while q:
    D, u = heapq.heappop(q)
    if D > d[u]:
        continue
    for v in g[u]:
        D2 = D + dist(ps[u], ps[v]) ** 0.5
        if D2 < d[v]:
            d[v] = D2
            heapq.heappush(q, (D2, v))

# Process queries
for _ in range(Q):
    u, T = map(int, input().split())
    u -= 1
    D = d[u]
    Q = T / D
    if Q < 2:
        print("impossible")
    else:
        c = Q - (Q**2 - 4) ** 0.5
        print(c * D)
