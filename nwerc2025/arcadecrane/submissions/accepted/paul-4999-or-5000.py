#!/usr/bin/env python3
import random

random.seed(987)

k = 3
n = int(input())
a = [int(x)-1 for x in input().split()]

steps = []

def make_step(i, j):
  global a, n, k
  steps.append((i, j))
  assert i != j
  assert max(i, j) <= n-k
  if i > j:
    a = a[:j] + a[i:i+k] + a[j:i] + a[i+k:]
  else:
    a = a[:i] + a[i+k:j+k] + a[i:i+k] + a[j+k:]

for i in reversed(range(2*k-1, n)):
  j = a.index(i)
  if j < k-1:
    make_step(0, k-1)
    j = a.index(i)
  if j != i:
    make_step(j-k+1, i-k+1)

while a != list(range(n)):
  i, j = random.sample(range(k), 2)
  make_step(i, j)

while len(steps) < 4999:
  i, j = random.sample(range(n-2), 2)
  make_step(i, j)
  make_step(j, i)

print(len(steps))
for i, j in steps:
  print(i+1, j+1)
