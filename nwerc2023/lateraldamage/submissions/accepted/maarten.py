#!/usr/bin/env python3

(n, k), sunk = map(int, input().split()), 0
hits = [(x, y) for y in range(1, n + 1) for x in range(1, n + 1) if (y - x) % 5 == 0 and input(f"{x} {y}\n") == "hit"]
for x, y in hits:
    for xx, yy in [*((xx, y) for xx in range(x - 4, x + 5)),
                   *((x, yy) for yy in range(y - 4, y + 5))]:
        if (xx, yy) not in hits and 1 <= xx <= n and 1 <= yy <= n:
            if input(f"{xx} {yy}\n") == "sunk":
                sunk += 1
                if sunk >= k: exit()
