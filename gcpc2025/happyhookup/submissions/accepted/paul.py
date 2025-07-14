#!/usr/bin/env python3

n, m = map(int, input().split())
adj = [[] for _ in range(n)]
for _ in range(m):
  a, b = [int(x)-1 for x in input().split()]
  adj[a].append(b)

def bfs(x):
  mark = [False] * n
  mark[x] = True
  todo = [x]
  for x in todo:
    for y in adj[x]:
      if not mark[y]:
        mark[y] = True
        todo.append(y)
  return mark

dpa, dpb = [bfs(int(x)-1) for x in input().split()]
res = [x for x in range(n) if dpa[x] and dpb[x]]
print('yes\n' + str(res[0]+1) if res else 'no')
