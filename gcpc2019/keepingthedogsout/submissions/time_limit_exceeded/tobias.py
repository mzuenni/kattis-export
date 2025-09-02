#!/usr/bin/env python3
# -*- coding: UTF-8 -*-

import sys
import math

if __name__ == "__main__":
    n = int(sys.stdin.readline())
    a = tuple(map(int, sys.stdin.readline().split()))
    area = sum(v << (2 * i) for i, v in enumerate(a))
    avail = list(i for i, v in enumerate(a) if v > 0)

    prefix, p = [0] * (n + 1), 0
    for i in range(n, -1, -1):
        p = 4 * p + a[i]
        prefix[i] = p

    for h in range(1, int(math.sqrt(area)) + 1):
        w = area // h
        if all(prefix[i] <= (h >> i) * (w >> i) for i in avail[::-1]):
            print("{0:d} {1:d}".format(h, w))
            sys.exit(0)
    print("impossible")
