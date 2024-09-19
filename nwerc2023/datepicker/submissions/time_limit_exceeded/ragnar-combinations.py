#!/usr/bin/env python3
import itertools

h, w = 7, 24
g = [input() for _ in range(h)]
r, c = map(int, input().split())
mx = 0
for rows in itertools.combinations(range(h), r):
    for cols in itertools.combinations(range(w), c):
        mx = max(mx, sum(1 for i in rows for j in cols if g[i][j] == "."))

print(mx / (r * c))
