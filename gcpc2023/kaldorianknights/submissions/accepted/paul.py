#!/usr/bin/env python3

P = 10**9 + 7

n, k = map(int, input().split())
a = [0]
for i in range(k):
  a.append(int(input()) + a[i])
a.append(n)

fac = [1] * (n+1)
for i in range(1, n+1):
  fac[i] = i*fac[i-1] % P

dp = [0] * (k+2)
for i in range(1, k+2):
  dp[i] = (fac[a[i]] - sum(fac[a[i]-a[j]] * dp[j] for j in range(i))) % P
print(dp[-1])
