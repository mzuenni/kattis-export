#!/usr/bin/env python3

n = int(input())
coins = [500, 200, 100, 20, 10, 5, 2, 1]
for k in range(2):
    r, dp, a = n, 1, []
    for c in coins[k:]:
        while r >= c:
            r -= c
            dp |= dp << c
            a.append(c)
    if n % 2 != 0 or dp & (1 << (n // 2)) == 0:
        # print('unsplittable')
        print(len(a))
        print(*a)
        exit(0)
print("splittable")
