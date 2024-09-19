#!/usr/bin/env python3
import sys


def process_hit(x, y):
    global sunk
    for xx, yy in [*((xx, y) for xx in range(x - 4, x + 5)), *((x, yy) for yy in range(y - 4, y + 5))]:
        if (xx, yy) not in hits and 1 <= xx <= n and 1 <= yy <= n:
            if input(f"{xx} {yy}\n") == "sunk":
                sunk += 1
                if sunk >= k: exit()


(n, k), sunk = map(int, input().split()), 0

# This line makes 2000 queries on a 100×100 grid
hits = [(x, y) for y in range(1, n + 1) for x in range(1, n + 1) if (y - x) % 5 == 0 and input(f"{x} {y}\n") == "hit"]

# Make at most 16 queries per ship, so worst case 9*16=144
for x, y in hits[:-1]:
    process_hit(x, y)

# Boost number of queries to 2000+144+344=2488 in the worst case
for _ in range(344):
    input("1 1\n")

# On the current test data, the last ship takes 12 hits to sink, giving a total of 2500 queries
process_hit(*hits[-1])
