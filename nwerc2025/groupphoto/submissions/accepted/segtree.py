#!/usr/bin/env python3

n = int(input())
nn = n + 2
t = [0] * (2 * nn)

def modify(p, value):
  p += nn
  t[p] = max(t[p], value)
  while p > 1:
    t[p // 2] = max(t[p], t[p ^ 1])
    p //= 2

def query(l, r):
  res = 0
  l += nn
  r += nn
  while l < r:
    if l % 2 == 1:
      res = max(res, t[l])
    if r % 2 == 1:
      res = max(res, t[r - 1])

    l = (l + 1) // 2
    r //= 2

  return res

v = []
a = list(map(int, input().split()))

right = [[] for i in range(n + 1)]
down = [[] for i in range(n + 1)]

for i in range(n):
  l = i + 1
  r = a[i] - i - 1

  if r >= 0:
    down[l].append(r)

  l = a[i] - n + i
  r = n - i
  if l >= 0:
    right[l].append(r)

for l in range(n + 1):
  down[l].sort()
  down[l].reverse()

  for r in down[l]:
    best = query(0, r + 1)
    modify(r, best + 1)

  right[l].sort()
  for r in right[l]:
    best = query(0, r)
    modify(r, best + 1)

ans = n - query(0, n + 1) 
print(ans)
