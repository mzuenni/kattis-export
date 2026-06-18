#!/usr/bin/env python3

n, m = map(int, input().split())
adj = [[] for _ in range(n)]
for _ in range(m):
  a, b = [int(x)-1 for x in input().split()]
  adj[a].append(b)
  adj[b].append(a)

def bfs(s):
  todo, dist = [s], [n] * n
  dist[s] = 0
  for a in todo:
    for b in adj[a]:
      if dist[b] == n:
        dist[b] = dist[a]+1
        todo.append(b)
  return dist

ds, dt = bfs(0), bfs(n-1)

for a in range(n):
  for b in adj[a]:
    if ds[a]+dt[b] == dt[0]:
      print('possible')
      exit(0)
print('impossible')
