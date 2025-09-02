#!/usr/bin/env python3
# -*- coding: UTF-8 -*-

import sys
import itertools


def score(string):
    if len(string) < 2:
        return len(string)
    index = (string + string).find(string, 1, 2 * len(string) + 1)
    if index == -1:
        return len(string)
    return index


if __name__ == "__main__":
    n = int(sys.stdin.readline())

    virus = sorted(tuple(map(score, (sys.stdin.readline().rstrip() for i in range(n)))))
    anti = sorted(tuple(map(score, (sys.stdin.readline().rstrip() for i in range(n)))))

    print(min(sum((xi - yi) ** 2 for xi, yi in zip(anti, permutation))
              for permutation in itertools.permutations(virus)))
