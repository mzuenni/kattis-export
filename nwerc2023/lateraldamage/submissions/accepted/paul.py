#!/usr/bin/env python3
import sys

n, k = map(int, input().split())
rem = 5*k

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

for i in range(n):
  for j in range(n):
    if (i+j)%5 == 0:
      query(i, j)
