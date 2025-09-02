#!/usr/bin/env python3
# -*- coding: UTF-8 -*-

import sys


def score(string):
    if len(string) < 2:
        return len(string)
    index = (string + string).find(string, 1, 2 * len(string) - 1)
    if index == -1:
        return len(string)
    return index


if __name__ == "__main__":
    # Matching problem: Sort scores, then compute euclidian distance
    n = int(sys.stdin.readline())

    virus = sorted(tuple(map(score, (sys.stdin.readline().rstrip() for _ in range(n)))))
    anti = sorted(tuple(map(score, (sys.stdin.readline().rstrip() for _ in range(n)))))

    print(sum((v - d) ** 2 for (v, d) in zip(virus, anti)))
