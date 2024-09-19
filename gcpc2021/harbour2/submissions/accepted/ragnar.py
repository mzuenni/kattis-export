#!/usr/bin/env python3
[n, l, r], L, R = (list(map(int, input().split())) for _ in range(3))

def inc(v):
    a = l = 0
    for x in v:
        l = max(x,l)
        if x == l: a += 1
    return a

ans = (1 if len(L) > 0 and L[-1] == 0 else 0) + (1 if len(R) > 0 and R[-1] == 0 else 0)
v = L + R[::-1]
z = v.index(0)
print(ans + inc(v[z-1-len(v)::-1]) + inc(v[z+1:]))
