#!/usr/bin/env python3
# -*- coding: UTF-8 -*-

import sys

if __name__ == "__main__":
    w, p = map(int, sys.stdin.readline().split())
    bribes = []

    for i in range(w):
        l = sys.stdin.readline().split()
        mine, their = int(l[0]), sorted(tuple(map(int, l[1:])), reverse=True)
        bribe_min, bribe_max = -1, sum(their)

        while bribe_max - bribe_min > 1:
            bribe = (bribe_min + bribe_max) // 2
            val = mine + bribe - 1
            votes_sum = 0
            for his in their:
                if his <= val:
                    break
                votes_sum += his - val
            if votes_sum <= bribe:
                bribe_max = bribe
            else:
                bribe_min = bribe
        bribes.append(bribe_max)

    bribes = sorted(bribes)
    print(sum(bribes[0:w // 2 + 1]))
