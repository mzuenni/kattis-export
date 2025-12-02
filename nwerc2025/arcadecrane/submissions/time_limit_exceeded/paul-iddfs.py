#!/usr/bin/env python3
import random

random.seed(987)

k = 3
n = int(input())
a = list(map(int, input().split()))

def dfs(a, ops, rem):
  if rem <= 0:
    return
  if a == list(range(1, n+1)):
    print(len(ops))
    for i, j in ops:
      print(i+1, j+1)
    exit(0)

  for i in random.sample(range(n-2), n-2):
    for j in random.sample(range(n-2), n-2):
      ops.append((i, j))
      if i < j:
        dfs(a[:i] + a[i+k:j+k] + a[i:i+k] + a[j+k:], ops, rem-1)
      elif i > j:
        dfs(a[:j] + a[i:i+k] + a[j:i] + a[i+k:], ops, rem-1)
      ops.pop()

for rem in range(10000):
  dfs(a, [], rem)
