#!/usr/bin/env python3
import sys, random

random.seed(int(sys.argv[1]))

h = int(sys.argv[2])
w = int(sys.argv[3])
cases = 2 ** (h * w) - 2
assert cases <= 10000
print(cases)
masks = list(range(2 ** (h * w)))
random.shuffle(masks)
for mask in masks:
    dat = ["." for i in range(h * w)]
    for i in range(h * w):
        if mask & (1 << i):
            dat[i] = "#"
    if len(set(dat)) == 1:
        continue
    print(h, w, dat.count('#'))
    for i in range(h):
        print("".join(dat[i * w: (i + 1) * w]))

