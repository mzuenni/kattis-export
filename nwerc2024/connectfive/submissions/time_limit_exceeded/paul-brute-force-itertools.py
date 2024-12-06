#!/usr/bin/env python3
import functools
import itertools

points = [list(map(int, input().split())) for _ in range(5)]
xs = sorted(set(x for x, _ in points))
ys = sorted(set(y for _, y in points))
cs = [xs.index(x) for x, _ in points]
ds = [ys.index(y) for _, y in points]

def segment(a, b, c, d):
  assert abs(c-a) + abs(d-b) == 1
  return 25 * (a != c) + 5 * min(a, c) + min(b, d)

def shortest_paths(a, b, c, d):
  if a == c and b == d:
    return [0]

  res = []
  for e, f in [(a+1, b), (a-1, b), (a, b-1), (a, b+1)]:
    if abs(c-e) + abs(d-f) < abs(c-a) + abs(d-b):
      res += [(1 << segment(a, b, e, f)) | mask for mask in shortest_paths(e, f, c, d)]
  return res

paths = [shortest_paths(cs[i], ds[i], cs[j], ds[j]) for i in range(5) for j in range(i)]

cost = [10**20] * 50
for a in range(len(xs)):
  for b in range(len(ys)):
    if a+1 < len(xs):
      cost[segment(a, b, a+1, b)] = xs[a+1]-xs[a]
    if b+1 < len(ys):
      cost[segment(a, b, a, b+1)] = ys[b+1]-ys[b]

res = 10**20
for v in itertools.product(*paths):
  mask = functools.reduce(lambda x, y: x | y, v)
  cur = sum(cost[k] for k in range(50) if mask & (1 << k))
  res = min(res, cur)
print(res)
