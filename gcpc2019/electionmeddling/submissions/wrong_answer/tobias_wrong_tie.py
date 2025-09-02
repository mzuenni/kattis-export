#!/usr/bin/env python3
# -*- coding: UTF-8 -*-

import sys

if __name__ == "__main__":
    w, p = map(int, sys.stdin.readline().split())
    bribes = [0] * w

    for i in range(w):
        l = tuple(map(int, sys.stdin.readline().split()))
        v0 = l[0]

        for v in l[1:]:
            if v0 < v:
                c = (v - v0 + 1) // 2
                v0 += c
                bribes[i] += c

    bribes = sorted(bribes)
    print(sum(bribes[0:w // 2 + 1]))
