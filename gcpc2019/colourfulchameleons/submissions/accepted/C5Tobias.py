#!/usr/bin/env python3
# -*- coding: UTF-8 -*-

import sys

if __name__ == "__main__":
    n, t, y = map(int, sys.stdin.readline().split())
    x = tuple(map(int, sys.stdin.readline().split()))

    if len(set(map(lambda v: v % (y + 1), x[:t - 1] + x[t:]))) > 1:
        print("impossible")
    else:
        u = max(x[:t - 1] + x[t:])
        s = sum(x) + u * (y - n + 1)
        print("{0:d} {1:d}".format(u, s))
