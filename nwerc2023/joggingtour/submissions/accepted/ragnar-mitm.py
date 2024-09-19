#!/usr/bin/env python3
import itertools

n = int(input())
ps = [tuple(map(int, input().split())) for _ in range(n)]

ans = float("inf")


def dist(i, j, dr):
    v = (ps[i][0] - ps[j][0], ps[i][1] - ps[j][1])
    return abs(v[0] * dr[0] + v[1] * dr[1]) + abs(v[0] * dr[1] - v[1] * dr[0])


def solve(dr):
    global ans
    l = (dr[0] ** 2 + dr[1] ** 2) ** 0.5
    g = [[dist(i, j, dr) for j in range(n)] for i in range(n)]
    m = {}
    for subset in range(1, 2**n + 1):
        for last in range(n):
            if subset == 1 << last:
                m[(subset, last)] = 0
                continue
            if bin(subset).count("1") * 2 > n + 2:
                continue
            if subset & (1 << last):
                s = subset ^ (1 << last)
                m[(subset, last)] = min(
                    m[(s, i)] + g[i][last] for i in range(n) if s & (1 << i)
                )

    s1 = n // 2 + 1
    local_ans = float("inf")
    for subset in range(1, 2**n + 1):
        if bin(subset).count("1") == s1:
            for last in range(n):
                if subset & 1 << last:
                    cmpl = (2**n - 1) ^ subset ^ (1 << last)
                    local_ans = min(local_ans, m[(subset, last)] + m[(cmpl, last)])
    ans = min(ans, local_ans / l)


for i in range(n):
    for j in range(i):
        dr = [ps[i][0] - ps[j][0], ps[i][1] - ps[j][1]]
        solve(dr)
print(ans)
