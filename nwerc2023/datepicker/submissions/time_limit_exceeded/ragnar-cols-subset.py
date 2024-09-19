#!/usr/bin/env python3
import itertools

h, w = 7, 24
g = [input() for _ in range(h)]
r, c = map(int, input().split())
mx = 0
for cols in itertools.combinations(range(w), c):
    cnts = []
    for i in range(h):
        cnt = 0
        for j in cols:
            if g[i][j] == ".":
                cnt += 1
        cnts.append(cnt)
    cnts.sort(reverse=True)
    mx = max(mx, sum(cnts[:r]))

print(mx / (r * c))
