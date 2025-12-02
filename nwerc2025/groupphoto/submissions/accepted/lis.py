#!/usr/bin/env python3
from bisect import bisect
n = int(input())
v = []
a = list(map(int, input().split()))
for i in range(n):
  if a[i] - i - 1 >= 0:
    v.append((2 * i + 1, 2 * (a[i] - i - 1)))
  if a[i] - n + i >= 0:
    v.append((2 * (a[i] - n + i), 2 * (n - i) - 1))
v.sort()
dp = [10 * n for i in range(len(v))]
ans = 0
for i in range(len(v)):
  pos = bisect(dp, v[i][1])
  dp[pos] = v[i][1]
  ans = max(ans, pos + 1)
print(n - ans)
