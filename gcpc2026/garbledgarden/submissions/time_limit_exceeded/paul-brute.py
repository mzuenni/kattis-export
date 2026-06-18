#!/usr/bin/env python3
import itertools

n = int(input())
s = tuple(map(int, input().split()))

dist, pred, todo = {(): -1}, {}, []

def consider(a, p, b):
  if b not in dist:
    dist[b] = dist[a] + 1
    pred[b] = (a, p)
    todo.append(b)
    if b == tuple(sorted(b)):
      res = []
      while b != s:
        b, p = pred[b]
        res.append(p)
      print(len(res))
      for p in res[::-1]:
        print(len(p))
        print(*[x+1 for x in p])
      exit(0)

consider((), None, s)
for a in todo:
  for k in range(1, n+1):
    for p in itertools.permutations(range(n), k):
      b = list(a)
      for i, j in zip(p, p[1:]):
        b[i], b[j] = b[j], b[i]
      consider(a, p, tuple(b))
