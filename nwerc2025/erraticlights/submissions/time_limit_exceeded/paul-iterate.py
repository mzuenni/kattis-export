#!/usr/bin/env python3
from collections import Counter, defaultdict

def normalize(a):
  return tuple(sorted(x for x in a if x > 0))

n, k = int(input()), 3

partitions = []
def rec(a, s, x):
  if s == 0:
    partitions.append(tuple(a))
  while x <= s:
    a.append(x)
    rec(a, s-x, x)
    a.pop()
    x += 1
rec([], n, 1)

idx = dict((a, i) for i, a in enumerate(partitions))

m = len(partitions)

adj = [[] for _ in range(m)]
for i, a in enumerate(partitions):
  go = defaultdict(int)
  go[a] += 1
  go[normalize([1, a[0]-1] + list(a[1:]))] += k-len(a)
  for j in range(1, len(a)):
    go[normalize([a[0]-1, a[j]+1] + list(a[1:j] + a[j+1:]))] += 1
  adj[i] = list((idx[b], c) for b, c in go.items())

dp = [0] * m
for z in range(100):
  for i in range(m-1):
    dp[i] = 1 + sum(c*dp[j] for j, c in adj[i]) / k

a = normalize(Counter(input()).values())
print(dp[idx[a]])
