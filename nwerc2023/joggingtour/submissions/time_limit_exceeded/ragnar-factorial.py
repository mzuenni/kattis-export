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
    for order in itertools.permutations(range(n)):
        ans = min(ans, sum(g[i][j] for i, j in zip(order, order[1:])) / l)


for i in range(n):
    for j in range(i):
        dr = [ps[i][0] - ps[j][0], ps[i][1] - ps[j][1]]
        solve(dr)
print(ans)
