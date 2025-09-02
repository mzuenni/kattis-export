#!/usr/bin/env python3
# -*- coding: UTF-8 -*-

import sys


def solve(ax, ay, r, bx, by, s):
    if r > s:
        return solve(bx, by, s, ax, ay, s)
    if ax > bx:
        x, y = solve(-ax, ay, r, -bx, by, s)
        return -x, y
    if ay > by:
        x, y = solve(ax, -ay, r, bx, -by, s)
        return x, -y

    d = bx - ax
    if r < d:
        return ax + r, ay
    return bx, ay + r - d


if __name__ == "__main__":
    ax, ay, r = map(int, sys.stdin.readline().split())
    bx, by, s = map(int, sys.stdin.readline().split())
    dx, dy = abs(bx - ax), abs(by - ay)
    gap = dx + dy - r - s

    if gap > 0 or gap % 2 != 0:
        print("impossible")
    else:
        x, y = solve(ax, ay, r, bx, by, s)
        print("{0:d} {1:d}".format(x, y))