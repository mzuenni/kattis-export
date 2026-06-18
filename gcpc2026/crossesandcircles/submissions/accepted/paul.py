#!/usr/bin/env python3

print(5, 5)
r, c = map(int, input().split())
if r == 5:
  print(4, 5)
  r, c = map(int, input().split())
  print(3 if r == 6 else 6, 5)
else:
  print(5, 4)
  r, c = map(int, input().split())
  print(5, 3 if c == 6 else 6)
