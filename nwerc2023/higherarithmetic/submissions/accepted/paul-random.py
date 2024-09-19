#!/usr/bin/env python3
import random
import sys

random.seed(987)
if len(sys.argv) >= 2:
  random.seed(int(sys.argv[1]))

input()
a = sorted(map(int, input().split()))
p = len([x for x in a if x == 1])
q = len([x for x in a if x == 2])
factors = [[x] for x in a[p+q:]]

if (p,q) == (1,0):
  if not factors:
    factors = [[]]
  factors[0].append(1)
else:
  while p+q > 0:
    options = [(1,1)]
    if q-p >= 1 or (p-q)%3 != 0:
      options += [(0,1)]
    if q-p >= 2 or (p-q)%3 == 1:
      options += [(0,2)]
    if p >= q and (p-q)%3 != 0:
      options += [(2,0)]
    if p >= q and (p-q)%3 == 1:
      options += [(2,1)]
    if p-q >= 1:
      options += [(3,0)]
    if p-q >= 2 and (p-q)%3 == 1:
      options += [(4,0)]
    options = [(i,j) for i, j in options if i <= p and j <= q and (p-i,q-j) != (1,0)]

    i, j = random.choice(options)
    p -= i
    q -= j
    factors.append([1]*i + [2]*j)

def show_factor(v):
  random.shuffle(v)
  return '(' + '+'.join(map(str, v)) + ')' if len(v) > 1 else str(v[0])

factors = [show_factor(v) for v in factors]
random.shuffle(factors)

if len(factors) == 1 and factors[0][0] == '(':
  print(factors[0][1:-1])
else:
  print('*'.join(factors))
