#!/usr/bin/env python3
import random
import sys

hmin, hmax, wmin, wmax, mode, s = map(int, sys.argv[1:])
random.seed(s)

h = random.randint(hmin, hmax)
w = random.randint(wmin, wmax)

a = [0] * 3
i, j, k = [x%3 for x in range(mode, mode+3)]

a[i] = (h if mode < 3 else w) + random.randint(-3, 3)
a[j] = random.randint(1, h*w-a[i]-1)
a[k] = h*w - a[i] - a[j]

print(h, w, *a)
