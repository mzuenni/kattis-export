#!/usr/bin/env python3

n, k, q = map(int, input().split())
events = []
for i in range(q):
  _, l, r = map(int, input().split())
  events.append((l, i))
  events.append((r, ~i))
events.sort()

depth = 0
need_key = [False] * q
for _, i in events:
  if depth == n:
    need_key[~i] = True
  depth += 1 if i >= 0 else -1

for _, i in events:
  k -= need_key[i] if i >= 0 else -need_key[~i]
  if k < 0:
    print('impossible')
    exit(0)

print(''.join('01'[b] for b in need_key))

