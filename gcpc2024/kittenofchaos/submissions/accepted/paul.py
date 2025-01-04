#!/usr/bin/env python3

s = input()
t = input()

def swap(s, c, d):
  return s.replace(c, 'x').replace(d, c).replace('x', d)

if len(t.replace('v', '')) % 2 == 1:
  s = swap(swap(s, 'b', 'd'), 'p', 'q')[::-1]
if len(t.replace('h', '')) % 2 == 1:
  s = swap(swap(s, 'b', 'p'), 'd', 'q')
print(s)
