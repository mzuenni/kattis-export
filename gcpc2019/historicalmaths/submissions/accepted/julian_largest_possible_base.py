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

mini = max(max(f1), max(f2), max(p)) + 1
maxi = 2 ** 64

while mini < maxi - 1:
    m = (mini + maxi) // 2
    if convert(f1, m) * convert(f2, m) < convert(p, m):
        maxi = m
    else:
        mini = m

if convert(f1, mini) * convert(f2, mini) == convert(p, mini):
    print(mini)
else:
    print("impossible")
