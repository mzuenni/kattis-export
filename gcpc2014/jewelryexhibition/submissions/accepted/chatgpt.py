import sys
from collections import deque

input = sys.stdin.readline

INF = 10 ** 9

R = int(input())

for _ in range(R):
    N, M, K = map(int, input().split())

    adj = [[] for _ in range(N)]

    for _ in range(K):
        x, y = map(float, input().split())
        c = int(x)
        r = int(y)
        adj[c].append(r)

    pairU = [-1] * N
    pairV = [-1] * M
    dist = [0] * N

    def bfs():
        q = deque()
        for u in range(N):
            if pairU[u] == -1:
                dist[u] = 0
                q.append(u)
            else:
                dist[u] = INF
        found = False
        while q:
            u = q.popleft()
            for v in adj[u]:
                w = pairV[v]
                if w == -1:
                    found = True
                elif dist[w] == INF:
                    dist[w] = dist[u] + 1
                    q.append(w)
        return found

    def dfs(u):
        for v in adj[u]:
            w = pairV[v]
            if w == -1 or (dist[w] == dist[u] + 1 and dfs(w)):
                pairU[u] = v
                pairV[v] = u
                return True
        dist[u] = INF
        return False

    matching = 0
    while bfs():
        for u in range(N):
            if pairU[u] == -1 and dfs(u):
                matching += 1

    print(matching)
