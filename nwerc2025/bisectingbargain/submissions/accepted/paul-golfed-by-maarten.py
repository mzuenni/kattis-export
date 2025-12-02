#!/usr/bin/env python3

n, coins = int(input()), [500, 200, 100, 50, 20, 10, 5, 2, 1]
for k in range(2):
    r, dp, a = n, 1, []
    for c in coins[k:]:
        while r >= c: r, dp, _ = r - c, dp | (dp << c), a.append(c)
    if n % 2 != 0 or dp & (1 << (n // 2)) == 0: exit(print(len(a), *a))
print("splittable")
