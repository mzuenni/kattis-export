#!/usr/bin/env python3
import heapq
from decimal import *

getcontext().prec = 100

n, m, q = map(int, input().split())
p = [list(map(int, input().split())) for _ in range(n)]

adj = [[] for _ in range(n)]
for _ in range(m):
  a, b = [int(x)-1 for x in input().split()]
  d4 = sum((u-v)**2 for u, v in zip(p[a], p[b]))
  d = Decimal(d4).sqrt().sqrt()
  adj[a].append((b, d))
  adj[b].append((a, d))

dist = [Decimal(1e100) for _ in range(n)]
dist[0] = Decimal(0)
pq = [(Decimal(0), 0)]

while pq:
  d, a = heapq.heappop(pq)
  if d > dist[a]:
    continue
  for b, d in adj[a]:
    if dist[a]+d < dist[b]:
      dist[b] = dist[a] + d
      heapq.heappush(pq, (dist[b], b))

for _ in range(q):
  a, t = map(int, input().split())
  s = dist[a-1]
  c = t/s
  if c < 2:
    print('impossible')
  else:
    b = c*c - 2
    u = Decimal(0.5) * (b - (b*b - 4).sqrt())
    print(f'{float(2*s*u.sqrt()):.10f}')
