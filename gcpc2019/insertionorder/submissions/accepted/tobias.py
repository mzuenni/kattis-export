#!/usr/bin/env python3
# -*- coding: UTF-8 -*-

import sys


def create_tree_balanced(start, end):
    if end < start:
        return
    mid = (start + end) // 2
    print(mid, end=" ")
    create_tree_balanced(start, mid - 1)
    create_tree_balanced(mid + 1, end)


def create_tree(start, end, depth_rem):
    if depth_rem <= 0:
        create_tree_balanced(start, end)
    else:
        mid = (start + end) // 2
        first = max(start, mid - depth_rem)
        for i in range(first, mid + 1):
            print(i, end=" ")
        create_tree_balanced(start, first - 1)
        create_tree(mid + 1, end, depth_rem - mid + first)


if __name__ == "__main__":
    n, k = map(int, sys.stdin.readline().split())

    i = n
    while i:
        k -= 1
        i //= 2
    if k < 0:
        print("impossible")
    else:
        create_tree(1, n, k)
        print()
