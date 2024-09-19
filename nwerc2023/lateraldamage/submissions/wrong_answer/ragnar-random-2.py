#!/usr/bin/env python3
# Improved of ragnar-random.py by also tracking non-hits.
import random

n, k = map(int, input().split())
qs = set()
hits = set()
nonhits = set()


def query(x, y):
    qs.add((x, y))
    if (x, y) in hits:
        return True
    if (x, y) in nonhits:
        return False
    print(x, y, flush=True)
    if input() != "miss":
        hits.add((x, y))
        if len(hits) == 5 * k:
            exit()
        return True
    else:
        nonhits.add((x, y))
        return False


while True:
    x, y = random.randint(1, n), random.randint(1, n)
    if (x, y) not in qs and query(x, y):
        q = []
        q.append((x, y))
        while q:
            x, y = q.pop()
            for dx, dy in ((1, 0), (-1, 0), (0, 1), (0, -1)):
                nx, ny = x + dx, y + dy
                if 1 <= nx <= n and 1 <= ny <= n:
                    if (nx, ny) not in qs and query(nx, ny):
                        q.append((nx, ny))
