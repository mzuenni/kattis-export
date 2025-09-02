#!/usr/bin/env python3
# -*- coding: UTF-8 -*-

import sys

if __name__ == "__main__":
    n, c = map(int, sys.stdin.readline().split())
    s = -c * (n - 1)
    for _ in range(n):
        m, ss = map(int, sys.stdin.readline().split(":"))
        s += 60 * m + ss
    print("{0:02d}:{1:02d}:{2:02d}".format(s // 3600, (s // 60) % 60, s % 60))
