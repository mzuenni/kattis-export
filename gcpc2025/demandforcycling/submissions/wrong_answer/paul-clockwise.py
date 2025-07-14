#!/usr/bin/env python3

n = int(input())
a = [list(map(int, input().split())) for _ in range(n)]

xmin = min(p[0] for p in a)
xmax = max(p[0] for p in a)
ymin = min(p[1] for p in a)
ymax = max(p[1] for p in a)

print(4)
print(xmin, ymin)
print(xmin, ymax)
print(xmax, ymax)
print(xmax, ymin)
