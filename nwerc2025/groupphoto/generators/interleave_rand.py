#!/usr/bin/python3
import sys
import random

# Creates a randomly interleaved sequence according to "mode", then performs
# k random swaps on top.

# Modes:
# 1 = Interleave ascending and descending sequence
# 2 = Interleave ascending sequences
# 3 = Interleave 1...k and k...n for random k

# Sel values:
# 1 = Strictly alternate between the two sequences
# 2 = Randomly alternate between the two sequences


random.seed(int(sys.argv[1]))
n = int(sys.argv[2])
mode = int(sys.argv[3])
sel = int(sys.argv[4])
swaps = int(sys.argv[5])

print(n)

l = []
r = []

if mode == 1 or mode == 2:
  for i in range(1, n + 1):
    if random.choice([True, False]):
      l.append(i)
    else:
      r.append(i)
else:
  k = random.randrange(0, n + 1)
  l = [i for i in range(1, k)]
  r = [i for i in range(k, n + 1)]

if mode == 1:
  r.reverse()

i = 0
li = 0
ri = 0
p = []

while li < len(l) or ri < len(r):
  useleft = i % 2 == 0
  if sel == 2:
    useleft = random.choice([True, False])
  if useleft and li < len(l):
    p.append(l[li])
    li += 1
  if not useleft and ri < len(r):
    p.append(r[ri])
    ri += 1

  i += 1

for nswap in range(swaps):
  i = random.randrange(n)
  j = random.randrange(n)
  p[i], p[j] = p[j], p[i]

print(*p)
