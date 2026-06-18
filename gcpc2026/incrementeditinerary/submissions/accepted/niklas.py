#!/usr/bin/env python3

from collections import defaultdict, deque

n, m = map(int, input().strip().split())
g = defaultdict(set)
for _ in range(m):
    u, v = map(int, input().strip().split())
    g[u].add(v)
    g[v].add(u)

dist = {1: 0}
parent = {}
q = deque()
q.append(1)
while q:
    u = q.popleft()
    for v in g[u]:
        if v not in dist:
            dist[v] = dist[u] + 1
            parent[v] = u
            q.append(v)

next_to_n = {n: n}
for u in sorted(dist, key=lambda v: dist[v], reverse=True):
    for v in g[u]:
        if dist[v] == dist[u] + 1 and v in next_to_n:
            next_to_n[u] = v
for u in dist:
    for v in g[u]:
        if dist[v] == dist[u] and v in next_to_n:
            # Path found
            print("possible")
            exit()

print("impossible")
