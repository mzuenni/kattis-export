#!/usr/bin/env python3

def free(grid, a, b):
  return 0 <= a < len(grid) and 0 <= b < len(grid[0]) and grid[a][b] == '.'

def neighbors(grid, a, b):
  pairs = [(a-1, b), (a, b-1), (a, b+1), (a+1, b)]
  return [(c, d) for c, d in pairs if free(grid, c, d)]

h, w = map(int, input().split())
glue = [input() for _ in range(h)]

dist = [[-1] * w for _ in range(h)]
queue = [(h-1, w-1)]
dist[-1][-1] = 0
for a, b in queue:
  for c, d in neighbors(glue, a, b):
    if dist[c][d] < 0:
      dist[c][d] = dist[a][b] + 1
      queue.append((c, d))

def combine(a, b):
  return '#' if '#' in [glue[a][b], glue[a][b+1], glue[a+1][b], glue[a+1][b+1]] else '.'
glue2 = [[combine(a, b) for b in range(w-1)] for a in range(h-1)]

comps = []
visited = [[False] * (w-1) for _ in range(h-1)]
for a in range(h-1):
  for b in range(w-1):
    if not visited[a][b] and free(glue2, a, b):
      queue = [(a, b)]
      visited[a][b] = True
      for c, d in queue:
        for e, f in neighbors(glue2, c, d):
          if not visited[e][f]:
            visited[e][f] = True
            queue.append((e, f))
      comps.append(list(set((e, f) for c, d in queue for e in [c, c+1] for f in [d, d+1])))

for a in range(h):
  for b in range(w):
    if free(glue, a, b) and free(glue, a+1, b) and not free(glue2, a, b-1) and not free(glue2, a, b):
      comps.append([(a, b), (a+1, b)])
    if free(glue, a, b) and free(glue, a, b+1) and not free(glue2, a-1, b) and not free(glue2, a, b):
      comps.append([(a, b), (a, b+1)])

a = [list(map(int, input().split())) for _ in range(h)]

def solve():
  perm = list(range(h*w))
  for comp in comps:
    comp.sort(key=lambda x: dist[x[0]][x[1]])
    p, q = set(), set()
    for i, j in comp[1:]:
      x, y = i*w+j+1, a[i][j]
      p.add(x)
      q.add(y)
      perm[x] = y
    if p != q:
      return False
    even = True
    for x in p:
      while perm[x] != x:
        y = perm[x]
        perm[x], perm[y] = perm[y], perm[x]
        even = not even
    if not even:
      return False
  return True

print('possible' if solve() else 'impossible')
