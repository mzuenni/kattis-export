#!/usr/bin/env python3

n, C = int(input()), sorted(__import__("collections").Counter(input()).values())
a, b, c = exit(print(0 if len(C) == 1 else 3 * C[0])) if len(C) <= 2 else C
print(1.5 * a + sum(__import__("math").comb(a, i) * 3 * min(b + i, c + a - i) for i in range(a + 1)) / 2 ** a)
