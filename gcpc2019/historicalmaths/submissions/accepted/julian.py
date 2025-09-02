#!/usr/bin/env python3

def convert(digits, base):
    f = 1
    result = 0
    for d in digits:
        result += f * d
        f *= base
    return result

f1 = [int(i) for i in input().split()[1::]][::-1]
f2 = [int(i) for i in input().split()[1::]][::-1]
p = [int(i) for i in input().split()[1::]][::-1]

mini = max(max(f1), max(f2), max(p))
maxi = 2 ** 64

while mini < maxi - 1:
    m = (mini + maxi) // 2
    if convert(f1, m) * convert(f2, m) <= convert(p, m):
        maxi = m
    else:
        mini = m

if convert(f1, maxi) * convert(f2, maxi) == convert(p, maxi):
    print(maxi)
else:
    print("impossible")
