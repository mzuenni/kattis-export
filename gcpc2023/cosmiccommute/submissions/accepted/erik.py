import math, sys
inp = lambda: list(map(int, sys.stdin.buffer.readline().split()))
n, m, k = inp()
adj, dp, w = [[] for i in range(n+1)], [-1] * (2*n+1), inp()
for i in range(m):
  u, v = inp()
  adj[u] += [v]
  adj[v] += [u]
def bfs(s, t):
  dp[s+t], q = 0, [s]
  for u in q:
    for v in adj[u]:
      if dp[v+t] == -1:
        dp[v+t] = dp[u+t] + 1
        q += [v]
bfs(1, 0); bfs(n, n)
t = min(min([(k - 1) * dp[i] - dp[i+n] for i in w]) + sum([dp[i+n] for i in w]), dp[n] * (k - 1))
g = math.gcd(t, k - 1)
print(t // g, (k - 1) // g, sep='/')