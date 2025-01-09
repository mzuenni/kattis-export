#!/usr/bin/env python3
import heapq
import math

n, m, q = map(int, input().split())
p = [list(map(int, input().split())) for _ in range(n)]

adj = [[] for _ in range(n)]
for _ in range(m):
  a, b = [int(x)-1 for x in input().split()]
  d4 = sum((u-v)**2 for u, v in zip(p[a], p[b]))
  d = d4 ** 0.25
  adj[a].append((b, d))
  adj[b].append((a, d))

dist = [1e100 for _ in range(n)]
dist[0] = 0
pq = [(0, 0)]

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
    u = 2 / (b + math.sqrt(b*b - 4))
    print(f'{2 * s * math.sqrt(u):.10f}')
