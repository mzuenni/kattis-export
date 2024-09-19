#!/usr/bin/env python3
import math

INF = 1e99

n = int(input())
pts = []
for i in range(n):
    [x,y] = input().split(' ')
    pts.append((int(x),int(y)))


def dist(i,j,angle):
    (vx,vy) = (pts[i][0] - pts[j][0], pts[i][1] - pts[j][1])
    rx = vx * math.cos(angle) + vy * math.sin(angle)
    ry = -vx * math.sin(angle) + vy * math.cos(angle)
    return abs(rx) + abs(ry)

def givenAngle(angle):
    # Dp state: places to visit, current place
    pw = 1 << n
    dp = [ [0] * n for _ in range(pw) ]
    for i in range(1,pw):
        for j in range(n):
            dp[i][j] = INF;
            for k in range(n):
                if (i & (1<<k)) == 0: continue
                if j == k: continue
                dp[i][j] = min(dp[i][j], dp[i^(1<<k)][k] + dist(j,k,angle))

    # Find the right starting place
    best = INF
    for i in range(n):
        best = min(best, dp[(1<<n)-(1<<i)-1][i])
    return best

best = None

for i in range(n):
    for j in range(i):
        angle = math.atan2(pts[i][0] - pts[j][0], pts[i][1] - pts[j][1])
        cur = givenAngle(-angle)
        if not best or cur < best:
            best = cur

print(best)
