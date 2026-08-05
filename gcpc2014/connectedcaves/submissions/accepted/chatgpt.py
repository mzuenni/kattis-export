import sys
from collections import deque

input = sys.stdin.readline

T = int(input())

for _ in range(T):
    N, E = map(int, input().split())
    val = [0] + list(map(int, input().split()))

    g = [[] for _ in range(N + 1)]
    indeg = [0] * (N + 1)

    for _ in range(E):
        a, b, c = map(int, input().split())
        g[a].append((b, c))
        indeg[b] += 1

    # Topological order
    q = deque(i for i in range(1, N + 1) if indeg[i] == 0)
    topo = []
    while q:
        u = q.popleft()
        topo.append(u)
        for v, _ in g[u]:
            indeg[v] -= 1
            if indeg[v] == 0:
                q.append(v)

    NEG = -10 ** 30
    dp = [NEG] * (N + 1)
    parent = [-1] * (N + 1)
    dp[1] = val[1]

    for u in topo:
        if dp[u] == NEG:
            continue
        for v, cost in g[u]:
            cand = dp[u] - cost + val[v]
            if cand > dp[v]:
                dp[v] = cand
                parent[v] = u

    end = 1
    for i in range(2, N + 1):
        if dp[i] > dp[end]:
            end = i

    path = []
    cur = end
    while cur != -1:
        path.append(cur)
        cur = parent[cur]
    path.reverse()

    print(dp[end], len(path))
    print(*path)
