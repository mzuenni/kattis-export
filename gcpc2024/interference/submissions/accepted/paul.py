#!/usr/bin/env python3

n, w = map(int, input().split())

updates = []
results = []
for _ in range(n):
  s = input()
  if s[0] == '!':
    updates.append(list(map(int, s[2:].split())))
  else:
    q = int(s[2:])
    res = 0
    for p, l, a in updates:
      if p <= q < p+l:
        res += [a, 0, -a, 0][(q-p)%4]
    results.append(res)

# print(len(results))
for res in results:
  print(res)
