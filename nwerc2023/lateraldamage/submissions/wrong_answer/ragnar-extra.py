#!/usr/bin/env python3
# Improved of ragnar-random.py by also tracking non-hits.
import random

n, k = map(int, input().split())
hits = set()


def query(x, y):
    print(x, y, flush=True)
    if input() != "miss":
        hits.add((x, y))
        if len(hits) == 5 * k:
            exit()
        return True
    else:
        return False


xs = list(range(1, n + 1))
ys = list(range(1, n + 1))
random.shuffle(xs)
random.shuffle(ys)
for x in xs:
    for y in ys:
        # NOTE: This should be %4
        if (x - y) % 4 == 3:
            query(x, y)

for x, y in hits.copy():
    for dx, dy in [(-1, 0), (1, 0), (0, -1), (0, 1)]:
        for l in range(1, 5):
            nx, ny = x + l * dx, y + l * dy
            if 1 <= nx <= n and 1 <= ny <= n:
                query(nx, ny)
