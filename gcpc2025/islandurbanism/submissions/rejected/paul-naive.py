#!/usr/bin/env python3
# @EXPECTED_RESULTS@: RUN_TIME_ERROR, TIME_LIMIT_EXCEEDED

n, m, _, k = map(int, input().split())
input()
adj = [[] for _ in range(n)]
for _ in range(m):
  a, b, c = map(int, input().split())
  adj[a-1].append((b-1, c))
  adj[b-1].append((a-1, c))
ts = [int(x)-1 for x in input().split()]

dp = [[10**18] * n for _ in range(1 << k)]
dp[0] = [0] * n
for i, t in enumerate(ts):
  dp[1 << i][t] = 0

done = False
while not done:
  done = True
  def consider(a, x, d):
    global done
    if d < dp[x][a]:
      dp[x][a] = d
      done = False
  for x in range(1 << k):
    for a in range(n):
      for y in range(1 << k):
        consider(a, x|y, dp[x][a] + dp[y][a])
      for b, c in adj[a]:
        consider(b, x, dp[x][a] + c)
print(min(dp[-1]))
