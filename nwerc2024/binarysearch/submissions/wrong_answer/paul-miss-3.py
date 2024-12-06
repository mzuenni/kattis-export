#!/usr/bin/env python3

n, m = map(int, input().split())
a = list(map(int, input().split()))

adj = [[] for _ in range(4*n)]
indeg = [0] * 4*n
def add_edge(x, y):
  i = 2 - 2*a[y] + a[x]
  j = 2*a[x] + a[y]
  adj[j*n + y].append(i*n + x)
  indeg[i*n + x] += 1

for _ in range(m):
  x, y = [int(z)-1 for z in input().split()]
  add_edge(x, y)
  add_edge(y, x)

dp = [0] * 4*n
todo = [x for x in range(4*n) if not indeg[x]]
for x in todo:
  for y in adj[x]:
    dp[y] = max(dp[y], dp[x]+1)
    indeg[y] -= 1
    if not indeg[y]:
      todo.append(y)

res = min(max(dp[i*n:(i+1)*n]) for i in range(4) if i != 3) + 2
print('infinity' if any(indeg) else 1 if len(set(a)) == 1 else res)
