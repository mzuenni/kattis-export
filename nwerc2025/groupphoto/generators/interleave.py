#!/usr/bin/python3
import sys

s = int(sys.argv[1])
inv = sys.argv[2] == 'inv'
n = 2 * s
print(n)

def num(k):
  if inv:
    return n - k + 1
  else:
    return k

p = [0 for i in range(n)]
for i in range(s):
  p[2 * i] = num(2 * i + 1)
  p[n - 2 * i - 1] = num(2 * i + 2)

print(*p)
