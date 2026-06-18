#!/usr/bin/env python3
import random
from collections import Counter

random.seed(987)

n = int(input())

while True:
  h, w = 8, 8
  while (h-6)*(w-6) < n:
    h += 2
    w += 2
  par, size = list(range(h*w+1)), [1] * h*w + [h*w+1]
  ctr = Counter(size)
  grid = [list('#' * w) for _ in range(h)]

  def find(i):
    while par[i] != i:
      i = par[i]
    return i

  def unite(i, j):
    i, j = random.sample([find(i), find(j)], 2)
    if i != j:
      par[i] = j
      ctr[size[i]] -= 1
      ctr[size[j]] -= 1
      size[j] += size[i]
      ctr[size[j]] += 1

  def clear(i, j):
    grid[i][j] = '.'
    for ni, nj in [(i-1, j), (i, j-1), (i, j+1), (i+1, j)]:
      if 0 <= ni < h and 0 <= nj < w:
        if grid[ni][nj] == '.':
          unite(i*w+j, ni*w+nj)
      else:
        unite(i*w+j, h*w)

  for i in range(0, h, 2):
    for j in range(0, w, 2):
      di, dj = divmod(random.randrange(4), 2)
      grid[i+di][j+dj] = 'O'
      clear(i+1-di, j+1-dj)

  cells = [(i, j) for i in range(0, h, 2) for j in range(0, w, 2)]
  random.shuffle(cells)
  cells.sort(key=lambda p: max(abs(p[0]-h/2), abs(p[1]-w/2)))

  for i, j in cells:
    for di in range(2):
      for dj in range(2):
        clear(i+di, j+dj)
    if ctr[n] > 0:
      print(h, w)
      for s in grid:
        print(''.join(s))
      exit(0)
