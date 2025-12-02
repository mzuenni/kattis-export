#!/usr/bin/env python3
from math import factorial

f = [factorial(i) for i in range(65)]


def b(n, k):
    return f[n] // (f[k] * f[n - k])


def solve():
    h, w, k = map(int, input().split())
    g = "".join(input().strip() for _ in range(h))
    n = h * w
    k = g.count("#")
    if b(n, k) % 2 != 0:
        print("risky", flush=True)
        return

    i = g.find("#")
    if i % 2 == 0:
        j = i + 1
    else:
        j = i - 1
    print(i // w + 1, i % w + 1)
    print(j // w + 1, j % w + 1, flush=True)


t = int(input())
for _ in range(t):
    solve()
