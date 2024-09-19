#!/usr/bin/env python3
import random

n, k = map(int, input().split())
hits = {}


def read(x, y):
    if input() != "miss":
        hits[(x, y)] = 1
        if len(hits) == 5 * k:
            exit()
        return True
    return False


while True:
    x, y = random.randint(1, n), random.randint(1, n)
    if (x, y) in hits:
        continue
    print(x, y, flush=True)
    if read(x, y):
        q = []
        q.append((x, y))
        while q:
            x, y = q.pop()
            for dx, dy in ((1, 0), (-1, 0), (0, 1), (0, -1)):
                nx, ny = x + dx, y + dy
                if 1 <= nx <= n and 1 <= ny <= n and (nx, ny) not in hits:
                    print(nx, ny, flush=True)
                    if read(nx, ny):
                        q.append((nx, ny))
