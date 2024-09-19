#!/usr/bin/env python3

import math

def bfs(adj, s):
  d = [-1] * len(adj)
  d[s] = 0
  q = [s]
  for a in q:
    for b in adj[a]:
      if d[b] == -1:
        d[b] = d[a]+1
        q.append(b)
  return d

n, m, k = map(int, input().split())
w = [int(x)-1 for x in input().split()]

adj = [[] for _ in range(n)]
for _ in range(m):
  a, b = [int(x)-1 for x in input().split()]
  adj[a].append(b)
  adj[b].append(a)

da = bfs(adj, 0)
db = bfs(adj, n-1)

s = sum(db[x] for x in w)
res = min([(k-1)*da[-1]] + [(k-1)*da[x] + s-db[x] for x in w])
g = math.gcd(res,k-1)
print(res//g,(k-1)//g,sep='/')
