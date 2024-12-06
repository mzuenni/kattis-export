#!/usr/bin/env python3
n = int(input())
ps = [list(map(int, input().split())) for _ in range(n)]
x = [_x for _x, _y in ps]
y = [_y for _x, _y in ps]

sum_x = sum(x)
sum_y = sum(y)

x = x + x
y = y + y

area = 0
for i in range(n):
    area += x[i] * y[i + 1] - x[i + 1] * y[i]

Sx = [0] * n
Sy = [0] * n
for i in range(1, n):
    Sx[0] += (i - 1) * x[i]
    Sy[0] += (i - 1) * y[i]
for i in range(1, n):
    Sx[i] = Sx[i - 1] - sum_x + x[i] + (n - 1) * x[i - 1]
    Sy[i] = Sy[i - 1] - sum_y + y[i] + (n - 1) * y[i - 1]

ans = 0
for i in range(n):
    ans -= x[i] * Sy[i]
    ans += y[i] * Sx[i]

print(ans / area)
