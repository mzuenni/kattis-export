#!/usr/bin/env python3
from functools import cache


def f(x):
    return (x + x)[::2]


def f_pow_k(base_f, k):
    if k == 0:
        return lambda x: x
    if k == 1:
        return base_f
    half_f = f_pow_k(base_f, k // 2)
    if k & 1:
        return cache(lambda x: base_f(half_f(half_f(x))))
    else:
        return cache(lambda x: half_f(half_f(x)))


(n, k), s = map(int, input().split()), input()
print(f_pow_k(f, k,)(s))
