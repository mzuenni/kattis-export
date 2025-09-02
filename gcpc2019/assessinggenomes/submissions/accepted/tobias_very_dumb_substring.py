#!/usr/bin/env python3
# -*- coding: UTF-8 -*-

import sys


def score(string):
    if len(string) < 2:
        return len(string)

    for i in range(1, len(string) // 2 + 1):
        if str(string[:i] * (len(string) // i)) == string:
            return i
    return len(string)


if __name__ == "__main__":
    # Matching problem: Sort scores, then compute euler distance
    n = int(sys.stdin.readline())

    virus = sorted(tuple(map(score, (sys.stdin.readline().rstrip() for _ in range(n)))))
    anti = sorted(tuple(map(score, (sys.stdin.readline().rstrip() for _ in range(n)))))

    print(sum((v - d) ** 2 for (v, d) in zip(virus, anti)))
