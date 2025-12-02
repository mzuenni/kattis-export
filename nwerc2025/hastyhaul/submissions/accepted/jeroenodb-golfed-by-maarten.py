#!/usr/bin/env python3


@__import__("functools").cache
def ways(a, b): return __import__("math").comb(a + b, b)


def rankof(s):
    a, b = s.count("1"), s.count("0")
    if a == 0 or b == 0: return 0
    if a == 1: return s.index("1")
    if s[-1] == "0": return rankof(s[:-1])
    ans = ways(a, b - 1)
    return ans + rankof(s[:-2][::-1]) if s[-2] == "0" else ans + ways(a - 1, b - 1) + rankof(s[:-2])


def kth(k, a, b):
    if a <= 1 or b == 0: return k * "0" + a * "1" + (b - k) * "0"
    if k < (c := ways(a, b - 1)): return kth(k, a, b - 1) + "0"
    if (k := k - c) < (c := ways(a - 1, b - 1)): return kth(k, a - 1, b - 1)[::-1] + "01"
    return kth(k - c, a - 2, b) + "11"


for _ in range(int(input())):
    (h, w, k), (x, y) = map(int, input().split()), (-1, -1)
    s = "".join(input() for i in range(h)).replace(".", "0").replace("#", "1")
    if __import__("math").comb(h * w, s.count("0")) % 2: print("risky")
    else:
        for i, (a, b) in enumerate(zip(s, kth(rankof(s) ^ 1, s.count("1"), s.count("0")))):
            if a != b: x, y = (i, y) if a == "1" else (x, i)
        print(1 + x // w, 1 + x % w, 1 + y // w, 1 + y % w)
