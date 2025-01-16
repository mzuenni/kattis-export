#!/usr/bin/env python3
from itertools import accumulate, permutations
import sys

n = int(input())
d = map(int, input().split())
s = [0] + list(accumulate(d))
m = 2*s[-1]

picks = []
for k in range(n+1):
    def who(i,b):
        return 2*(s[i + 5*(k==n)] + abs(b) - 1) + (b < 0)
    picks.append([who(i,b) for i, b in enumerate(map(int, input().split()))])

def dfs(adj, mark, order, a):
    stack = [(a,0)]
    while stack:
        a, k = stack.pop()
        mark[a] = True
        if k < len(adj[a]):
            b = adj[a][k]
            stack.append((a,k+1))
            if not mark[b]:
                stack.append((b,0))
        else:
            order.append(a)

adj = [[] for _ in range(m)]
radj = [[] for _ in range(m)]
def add_edge(a, b):
    adj[a].append(b)
    radj[b].append(a)

for i in range(n):
    for a, b in permutations(picks[i], 2):
        add_edge(a, b^1)

for a in picks[-1]:
    add_edge(a^1, a)

mark = [0] * m
order = []
for a in range(m):
    if not mark[a]:
        dfs(adj, mark, order, a)

res = True
mark = [0] * m
for a in order[::-1]:
    if not mark[a]:
        comp = []
        dfs(radj, mark, comp, a)
        comp = set(comp)
        if any((a^1) in comp for a in comp):
            res = False

print('possible' if res else 'impossible')
