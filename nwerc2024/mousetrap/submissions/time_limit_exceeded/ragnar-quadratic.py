#!/usr/bin/env python3
n = int(input())
ps = [list(map(int, input().split())) for _ in range(n)]
xs = [x for x, y in ps]
ys = [y for x, y in ps]
xs = xs + xs
ys = ys + ys

area = 0
for i in range(n):
    area += xs[i] * ys[i + 1] - xs[i + 1] * ys[i]

ans = 0
for i in range(n):
    for j in range(i + 1, i + n):
        ans += (xs[j] * ys[i] - xs[i] * ys[j]) * (j - i - 1)

print(ans / area)
