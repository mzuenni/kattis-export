#!/usr/bin/env python3

n, m, k = map(int, input().split())
g = [[] for _ in range(n)]
for _ in range(m):
    i, j, l = map(int, input().split())
    g[i - 1].append((j - 1, l))
    g[j - 1].append((i - 1, l))

s = 0
t = n - 1

inf = 10**15

from heapq import heappop, heappush


def dijkstra(s):
    dist = [inf] * n
    dist[s] = 0
    q = [(0, s)]
    while q:
        d, u = heappop(q)
        if d != dist[u]:
            continue
        for v, w in g[u]:
            if dist[u] + w < dist[v]:
                dist[v] = dist[u] + w
                heappush(q, (dist[v], v))
    return dist


dists = [d1 + d2 for d1, d2 in zip(dijkstra(s), dijkstra(t))]

special = []
for _ in range(k):
    i, p = input().split()
    i = int(i) - 1
    d = dists[i]
    p = float(p)
    special.append((d, p))
special.sort()
ans = 0
p = 1
for d, pp in special:
    if d >= inf:
        break
    ans += d * p * pp
    if pp == 1:
        print(ans)
        exit(0)
    p *= 1 - pp
print("impossible")
