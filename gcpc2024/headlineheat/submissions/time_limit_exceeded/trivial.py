#!/usr/bin/env python3

n,m,k = map(int, input().split())
names = [input() for _ in range(n)]
edges = []
for _ in range(m):
    u,v = map(int, input().split())
    edges.append((u-1,v-1))
texts = [input() for _ in range(k)]

for t in texts:
    mad = 0
    for u,v in edges:
        occ1 = t.count(names[u])
        occ2 = t.count(names[v])
        mad += (occ1 != occ2)
        if mad > 0: break
    print("no" if mad>0 else "yes")

