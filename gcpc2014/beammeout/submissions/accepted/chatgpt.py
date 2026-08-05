import sys
from collections import deque

input = sys.stdin.readline

n = int(input())

g = [[] for _ in range(n + 1)]
rg = [[] for _ in range(n + 1)]

for u in range(1, n):
    m = int(input())
    if m:
        arr = list(map(int, input().split()))
    else:
        input()
        arr = []
    g[u] = arr
    for v in arr:
        rg[v].append(u)

# Reachable from room 1
reach = [False] * (n + 1)
dq = deque([1])
reach[1] = True
while dq:
    u = dq.popleft()
    for v in g[u]:
        if not reach[v]:
            reach[v] = True
            dq.append(v)

# Can reach room n (reverse BFS)
good = [False] * (n + 1)
dq = deque([n])
good[n] = True
while dq:
    u = dq.popleft()
    for v in rg[u]:
        if not good[v]:
            good[v] = True
            dq.append(v)

pardon = True
for i in range(1, n + 1):
    if reach[i] and not good[i]:
        pardon = False
        break

# Cycle detection on reachable subgraph
sys.setrecursionlimit(200000)

color = [0] * (n + 1)
cycle = False

def dfs(u):
    global cycle
    color[u] = 1
    for v in g[u]:
        if not reach[v]:
            continue
        if color[v] == 0:
            dfs(v)
            if cycle:
                return
        elif color[v] == 1:
            cycle = True
            return
    color[u] = 2

for i in range(1, n + 1):
    if reach[i] and color[i] == 0:
        dfs(i)
        if cycle:
            break

print(
    ("PARDON" if pardon else "PRISON"),
    ("LIMITED" if not cycle else "UNLIMITED"),
)
