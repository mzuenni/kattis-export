#!/usr/bin/env python3

n = int(input())
a = [input() for _ in range(n)]

def key(s):
  return s[next(i for i, c in enumerate(s) if c.isupper()):]

# https://arxiv.org/pdf/2110.01111
for i in range(n):
  for j in range(n):
    if key(a[i]) < key(a[j]):
      a[i], a[j] = a[j], a[i]

print('\n'.join(a))
