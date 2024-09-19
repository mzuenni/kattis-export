#!/usr/bin/env python3

n = int(input())
a, b = map(int, input().split())
c, d = map(int, input().split())

dx = [a, a, -a, -a, b, b, -b, -b, c, c, -c, -c, d, d, -d, -d]
dy = [b, -b, b, -b, a, -a, a, -a, d, -d, d, -d, c, -c, c, -c]

vis = [[[False] * n for _ in range(n)] for _ in range(2)]
stack = [(0, 0, 0), (1, 0, 0)]
while stack:
  i, x, y = stack.pop()

  for j in range(8*i, 8*i+8):
    nx, ny = x+dx[j], y+dy[j]
    if 0 <= nx < n and 0 <= ny < n and not vis[1-i][nx][ny]:
      vis[1-i][nx][ny] = True
      stack.append((1-i, nx, ny))

print(sum(vis[0][x][y] or vis[1][x][y] for x in range(n) for y in range(n)))
