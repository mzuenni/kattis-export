#!/usr/bin/env python3
import random

random.seed(987)

n = int(input())
ps = [list(map(int, input().split())) for _ in range(n)]

def collinear(a, b, c):
    return (b[0]-a[0])*(c[1]-a[1]) == (b[1]-a[1])*(c[0]-a[0])

def solve():
    for _ in range(50):
        a, b = random.sample(ps, 2)
        qs = [c for c in ps if not collinear(a, b, c)]
        if len(qs) < 2:
            return True
        c, d = random.sample(qs, 2)
        rs = [e for e in qs if not collinear(c, d, e)]
        if len(rs) < 2:
            return True
        e, f = random.sample(rs, 2)
        if all(collinear(e, f, g) for g in rs):
            return True
    return False

print('possible' if solve() else 'impossible')
