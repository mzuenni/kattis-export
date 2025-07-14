#!/usr/bin/env python3

h, w = map(int, input().split())
a = [input() for _ in range(h)]

total = sum(s.count('#') for s in a)

def solve(n):
  mark = [[False] * w for _ in range(h)]
  for i in range(h):
    for j in range(w):
      if a[i][j] == '#' and not mark[i][j]:
        if i+n > h or j+n > w:
          return False
        for di in range(n):
          for dj in range(n):
            if a[i+di][j+dj] == '.' or mark[i+di][j+dj]:
              return False
            mark[i+di][j+dj] = True
  return True

for n in range(min(h, w), 0, -1):
  if total % (n*n) == 0 and solve(n):
    print(n)
    break
