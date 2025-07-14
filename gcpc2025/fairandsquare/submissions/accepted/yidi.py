n, m = map(int, input().split())
a = [input() for i in range(n)]

cnt = sum(s.count('#') for s in a)

ans = 1
for x in range(1, n+1):
    if cnt % (x*x) != 0:
        continue

    cnt2 = cnt / x / x
    vis = [[False]*m for i in range(n)]
    for i in range(n-x+1):
        for j in range(m-x+1):
            if not vis[i][j] and a[i][j] == '#':
                cnt2 -= 1
                for k in range(x):
                    for l in range(x):
                        if a[i+k][j+l] != '#' or vis[i+k][j+l]:
                            cnt2 = -1
                        vis[i+k][j+l] = True

    if not cnt2:
        ans = x

print(ans)
