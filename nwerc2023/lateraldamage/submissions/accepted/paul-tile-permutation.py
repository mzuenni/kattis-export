#!/usr/bin/env python3
import random
import sys

n, k = map(int, input().split())
rem = 5*k
random.seed(n + 1000*k)

hits = []
def query(i, j):
  global rem
  if rem == 0 or not (0 <= i < n and 0 <= j < n):
    return
  print(i+1, j+1)
  sys.stdout.flush()
  if input() != 'miss':
    rem -= 1
    query(i+1, j)
    query(i-1, j)
    query(i, j-1)
    query(i, j+1)

perm = list(range(5))
random.shuffle(perm)

for i in range(n):
  for j in range(n):
    if perm[i%5] == j%5:
      query(i, j)
