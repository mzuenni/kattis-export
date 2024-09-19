#!/usr/bin/env python3

a = list(map(int, input().split()))
lo, hi = sum(a), sum(x*y for x, y in zip(a, [4,6,8,12,20]))
md = (lo+hi)/2
res = list(range(lo, hi+1))
res.sort(key=lambda x: abs(x-md))
print(*res)
