#!/usr/bin/env python3
import sys, random

random.seed(int(sys.argv[1]))

h = int(sys.argv[2])
w = int(sys.argv[3])
k = -1 if len(sys.argv) == 4 else int(sys.argv[4])
t = random.randint(5000, 10000)

randomSizes = (h == -1)
randomK = (k == -1)

print(t)
for _ in range(t):
    if randomSizes:
        h = w = 1
        while h == 1 and w == 1: 
            h = random.randint(1, 8)
            w = random.randint(1, 8)
    if randomK:
        k = random.randint(1, h * w - 1)
    print(h, w, k)
    dat = ["#" for _ in range(k)]
    dat += ["." for _ in range(h * w - k)]
    random.shuffle(dat)
    for i in range(h):
        print("".join(dat[i * w: (i + 1) * w]))
