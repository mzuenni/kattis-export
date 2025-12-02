#!/usr/bin/env python3

adj, ans, _ = [[] for _ in range(int(input()))], 0, __import__("sys").setrecursionlimit(4 * 10**5)
for i in range(len(adj) - 1):
    u, v, w = map(int, input().split())
    adj[u - 1].append((v - 1, w)), adj[v - 1].append((u - 1, w))

deg, m = [False] * len(adj), int(input())
for i in range(m):
    for u in map(int, input().split()): deg[u - 1] = not deg[u - 1]


def dfs(at, frm) -> bool:
    global ans
    cur = deg[at] % 2 == 1
    for to, w in adj[at]:
        if to != frm and dfs(to, at): ans, cur = ans + w, not cur
    return cur


dfs(0, -1), print(ans)
