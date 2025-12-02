#!/usr/bin/env python3
import random
import sys

h, w, mode, s = map(int, sys.argv[1:])
random.seed(s)

a = [0] * 3
i, j, k = [x%3 for x in range(mode, mode+3)]

if mode < 3:
  a[i] = 1
  a[j] = random.randrange(1, h*w-2)
  a[k] = h*w - 1 - a[j]
else:
  a[i] = 1
  a[j] = 1
  a[k] = h*w - 2

print(h, w, *a)
