#!/usr/bin/env python3

s = input()
t = input()

def swap(s, c, d):
  return s.replace(c, 'x').replace(d, c).replace('x', d)

t = t.replace('r', 'hv')
while len(t) > 3:
  t = t.replace('hh', '')
  t = t.replace('vv', '')
  t = t.replace('hvhv', '')

for c in t:
  if c == 'h':
    s = swap(swap(s, 'b', 'd'), 'p', 'q')[::-1]
  else:
    s = swap(swap(s, 'b', 'p'), 'd', 'q')

print(s)
