#!/usr/bin/env python3
import itertools

h, w = 7, 24
g = [input() for _ in range(h)]
r, c = map(int, input().split())
mx = 0
for rows in itertools.combinations(range(h), r):
    cnts = []
    for j in range(w):
        cnt = 0
        for i in rows:
            if g[i][j] == ".":
                cnt += 1
        cnts.append(cnt)
    cnts.sort(reverse=True)
    mx = max(mx, sum(cnts[:c]))

print(mx / (r * c))
