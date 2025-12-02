#!/usr/bin/env python3
import random

random.seed(987)

h, w, k, i, t = map(int, input().split())

def check(a):
  def has(i, j, c):
    return 0 <= i < h and 0 <= j < w and a[i][j] == c

  count = 0
  for i in range(h):
    for j in range(w):
      for di in range(-1, 2):
        for dj in range(-1, 2):
          count += all(has(i+di*k, j+dj*k, c) for k, c in enumerate('KIT'))
          if count > 1:
            return False
  return count == 1

s = list('K' * k + 'I' * i + 'T' * t)
while True:
  random.shuffle(s)
  a = [s[i:i+w] for i in range(0, h*w, w)]
  if check(a):
    print('\n'.join(''.join(v) for v in a))
    break
