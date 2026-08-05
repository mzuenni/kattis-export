import sys
import math

input = sys.stdin.readline

T = int(input())

for _ in range(T):
    n = int(input())
    p = [tuple(map(int, input().split())) for _ in range(n)]

    dist = [[0.0] * n for _ in range(n)]
    for i in range(n):
        x1, y1 = p[i]
        for j in range(i + 1, n):
            x2, y2 = p[j]
            d = math.hypot(x1 - x2, y1 - y2)
            dist[i][j] = dist[j][i] = d

    INF = 1e100
    dp = [[INF] * n for _ in range(n)]
    dp[0][1] = dist[0][1]

    for j in range(2, n):
        for i in range(j - 1):
            dp[i][j] = dp[i][j - 1] + dist[j - 1][j]

        best = INF
        for k in range(j - 1):
            best = min(best, dp[k][j - 1] + dist[k][j])
        dp[j - 1][j] = best

    ans = dp[n - 2][n - 1] + dist[n - 2][n - 1]
    print("{:.12f}".format(ans))
