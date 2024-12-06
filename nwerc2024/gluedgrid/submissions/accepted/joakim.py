#!/usr/bin/env python3
n, m = map(int,input().split())
s = [input() for i in range(n)]
p = [0] + [int(a) for i in range(n) for a in input().split()][:-1]

at = lambda i,j: (i*m+j+1)%(n*m)
q = [(n-1,m-1)]
vis = [0]*(n*m)
vis[at(n-1,m-1)] = 1
for x,y in q:
  for dx,dy in [(0,1),(0,-1),(-1,0),(1,0)]:
    nx, ny = x+dx, y+dy
    if 0 <= nx < n and 0 <= ny < m and s[nx][ny] == '.' and not vis[at(nx,ny)]:
      vis[at(nx,ny)] = 1+len(q)
      q.append((nx,ny))

uf = list(range(n*m))
def fnd(x):
  uf[x] = fnd(uf[x]) if uf[x] != x else x
  return uf[x]

for i in range(n-1):
  for j in range(m-1):
    v = sorted([at(i,j),at(i+1,j),at(i,j+1),at(i+1,j+1)], key = lambda x: vis[x])
    if vis[v[0]]:
      uf[fnd(v[1])] = uf[fnd(v[2])] = fnd(v[3])

component = [[] for i in range(n*m)]
for i in range(n*m):
  component[fnd(i)].append(i)
  if fnd(i) != fnd(p[i]):
    print("impossible")
    exit()

for l in component:
  parity = False
  for x in l:
    while p[x] != x:
      p[p[x]], p[x] = p[x], p[p[x]]
      parity = not parity
  if parity:
    print("impossible")
    exit()

print("possible")
