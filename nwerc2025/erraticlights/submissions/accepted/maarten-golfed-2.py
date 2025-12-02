#!/usr/bin/env python3

# We can pretend we always have three colours of lights, and have the lowest counts be equal to 0.
n, (a, b, c) = input(), ([0] * 3 + sorted(__import__("collections").Counter(input()).values()))[-3:]
print(1.5 * a + sum(__import__("math").comb(a, i) * 3 * min(b + i, c + a - i) for i in range(a + 1)) / 2 ** a)
