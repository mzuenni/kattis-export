#!/usr/bin/env python3

n = int(input())
a = [input() for _ in range(n)]
a.sort()
for s in a:
  print(s)
