#!/usr/bin/env python3
from collections import defaultdict

events = defaultdict(list)
for _ in range(int(input())):
  a, b = input().split()
  events[b].append(a)

res = all(l == ['pickup', 'dropoff'] for l in events.values())
print('yes' if res else 'no')
