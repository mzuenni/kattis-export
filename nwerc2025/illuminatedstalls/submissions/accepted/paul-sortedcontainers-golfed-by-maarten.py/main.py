#!/usr/bin/env python3
from sortedlist import SortedList

# Using https://github.com/grantjenks/python-sortedcontainers

def solve():
  n, events, crossings, cross_xor, active = int(input()), [], 0, {}, SortedList()
  a, adj = [tuple(map(int, input().split())) for _ in range(n)], [[] for _ in range(n)]

  for i, (p, q, r, s) in enumerate(a):
    if p == r: events += [(p, 0, i)]
    else: events += [(p, -1, i), (r, 1, i)]
  events.sort()

  by_length = sorted([(r+s-p-q, i) for i, (p, q, r, s) in enumerate(a)] + [(0, n)], reverse=True)

  def lw(v): return next(z for z, i in by_length if i not in v)

  for x, t, i in events:
    if t == 0:
      k = active.bisect_left((a[i][1], -1))
      while k < len(active):
        y, j = active[k]
        if y > a[i][3]: break
        adj[i].append(j), adj[j].append(i)
        cross_xor[(x, y)] = i ^ j
        if (crossings := crossings + 1) > 4*n: return True
        k += 1
    elif t == -1: active.add((a[i][1], i))
    else: active.remove((a[i][1], i))

  for _ in range(2):
    for i in range(n):
      if a[i][0] != a[i][2]:
        y = a[i][1]
        for above in range(2):
          stk = []
          for j in adj[i]:
            x, h = a[j][0], a[j][3] - y if above else y - a[j][1]
            while stk and stk[-1][0] < x: stk.pop()
            if stk:
              side = x - (px := a[k := stk[-1][1]][0])
              py = y + (side if above else -side)
              if h >= side:
                p, q, l, m, bl, bm = (px, py), (x, py), -1, -1, 0, 0
                if p in cross_xor: bl = a[l := k ^ cross_xor[p]][2] - px
                if q in cross_xor: bm = x - a[m := j ^ cross_xor[q]][0]
                if lw([i, j, k, l, m]) >= side-bl-bm or lw([i, j, k, l]) >= side-bl or lw([i, j, k, m]) >= side-bm:
                  return True
            stk.append((h+x, j))

    a = [(q, p, s, r) for p, q, r, s in a]
    cross_xor = dict(((q, p), z) for (p, q), z in cross_xor.items())
  return False

for _ in range(int(input())): print('yes' if solve() else 'no')
