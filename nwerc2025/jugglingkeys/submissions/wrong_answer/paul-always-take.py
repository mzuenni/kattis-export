#!/usr/bin/env python3

# If there are still keys left when leaving the apartment, take one.

n, k, q = map(int, input().split())
events = []
for i in range(q):
  j, l, r = map(int, input().split())
  events.append((l, i, j-1))
  events.append((r, ~i, j-1))
events.sort()

away = 0
use_key = [False] * q
has_key = [False] * n
for _, i, j in events:
  if i >= 0:
    away += 1
    use_key[i] = k > 0
    if use_key[i]:
      k -= 1
      has_key[j] = True
  else:
    if away == n and not has_key[j]:
      print('impossible')
      exit(0)
    away -= 1
    k += has_key[j]
    has_key[j] = False

print(''.join('01'[b] for b in use_key))
