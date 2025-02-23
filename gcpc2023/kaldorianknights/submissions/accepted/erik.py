#!/usr/bin/env python3
n, k = map(int, input().split())
f, dp, a, mod = [1] * (n + 1), [0] * (k + 1), [], 10 ** 9 + 7
for i in range(1, n + 1):
  f[i] = f[i - 1] * i % mod
dp[0], ans = 1, f[n]
for i in range(1, k + 1):
  a += [int(input())]
  s = 0
  for j in range(i - 1, -1, -1):
    s += a[j]
    dp[i] -= dp[j] * f[s]
  dp[i] %= mod
  ans += dp[i] * f[n - s]
print(ans % mod)
