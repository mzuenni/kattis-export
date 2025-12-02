#!/usr/bin/env python3
import random
import sys

s = int(sys.argv[1])
random.seed(s)

h = random.randint(3, 100)
w = random.randint(3, 100)

mode = random.randrange(6)

a = [0] * 3
i, j, k = [x%3 for x in range(mode, mode+3)]

if mode < 3:
  a[i] = random.randint(1, min(10, h*w-2))
  a[j] = random.randrange(1, h*w-a[i]-1)
  a[k] = h*w - a[i] - a[j]
else:
  a[i] = random.randint(1, min(10, h*w-2))
  a[j] = random.randint(1, min(10, h*w-a[i]-1))
  a[k] = h*w - a[i] - a[j]

print(h, w, *a)
