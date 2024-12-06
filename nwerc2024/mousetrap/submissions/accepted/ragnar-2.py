#!/usr/bin/env python3
n = int(input())
ps = [list(map(int, input().split())) for _ in range(n)]
x = [_x for _x, _y in ps]
y = [_y for _x, _y in ps]

sum_x, sum_y = sum(x), sum(y)

Sx = sum(i * x[i] for i in range(n))
Sy = sum(i * y[i] for i in range(n))

ans, area = 0, 0
for i in range(n):
    ans += y[i] * Sx - x[i] * Sy
    area += x[i - 1] * y[i] - x[i] * y[i - 1]

    Sx += n * x[i] - sum_x
    Sy += n * y[i] - sum_y


print(ans / area)
