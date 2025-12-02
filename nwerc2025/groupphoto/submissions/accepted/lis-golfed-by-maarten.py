#!/usr/bin/env python3
n, a, ans = int(input()), list(map(int, input().split())), 0
v = sorted([(2 * i + 1, 2 * (a[i] - i - 1)) for i in range(n) if a[i] - i - 1 >= 0]
         + [(2 * (a[i] - n + i), 2 * (n - i) - 1) for i in range(n) if a[i] - n + i >= 0])
dp = [10 * n for _ in range(len(v))]
for i in range(len(v)):
    dp[pos := __import__("bisect").bisect(dp, v[i][1])] = v[i][1]
    ans = max(ans, pos + 1)
print(n - ans)
