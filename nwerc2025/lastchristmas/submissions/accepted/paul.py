#!/usr/bin/env python3

n = int(input())
lists = [list(input().split()) for _ in range(n)]

def count_at(name, idx):
  return sum(l[idx] == name for l in lists)

def score(name):
  counts = [count_at(name, i) for i in range(10)]
  return [sum(counts)] + counts

names = set(s for l in lists for s in l)
best = max(names, key=score)
if sum(score(s) == score(best) for s in names) > 1:
  best = 'tie'
print(best)
