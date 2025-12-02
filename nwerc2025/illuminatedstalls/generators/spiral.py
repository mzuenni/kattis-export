#!/usr/bin/python3
import sys

n = int(sys.argv[1])
mid = int(sys.argv[2])
skew = int(sys.argv[3])

print(1)
print(n)
x, y = mid, mid

dirs = [(1, 0), (0, 1), (-1, 0), (0, -1)]

for i in range(1, n + 1):
    len = i
    if i % 2 == 0:
        len += skew
    nx = x + len * dirs[(i - 1) % 4][0]
    ny = y + len * dirs[(i - 1) % 4][1]
    print(min(x, nx), min(y, ny), max(x, nx), max(y, ny))
    x, y = nx, ny
