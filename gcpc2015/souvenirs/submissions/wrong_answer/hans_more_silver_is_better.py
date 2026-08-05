
G, C, N = [int(x) for x in input().split(' ')]
souv = [input().split(' ') for _ in range(N)]
souv = [(str(h), int(p), int(s)) for h, p, s in souv]

# res, N, C = silver
dp = [[[-1 for _ in range(C+1)] for _ in range(N+1)] for _ in range(N+1)]

dp[0][0][C] = 0

result = 0
def update(r, n ,c, val):
    dp[r][n][c] = max(dp[r][n][c], val)

for res in range(N):
    for n in range(N):
        attitude, pkg, price = souv[n]
        change = G - price
        for c in range(C+1):
            silver = dp[res][n][c]
            if silver == -1:
                continue

            # don't buy
            update(res, n+1, c, silver)

            if silver >= price:
                update(res+1, n+1, c, silver - price)

            if c < 1:
                continue

            if attitude == 'greedy':
                real_change = (change // pkg) * pkg
                update(res+1, n+1, c-1, silver + real_change)
            elif attitude == 'honest':
                low_change = (change // pkg) * pkg
                high_change = ((change + pkg - 1) // pkg) * pkg
                if change - low_change < high_change - change:
                    real_change = low_change
                else:
                    real_change = high_change
                update(res+1, n+1, c-1, silver + real_change)
            elif attitude == 'generous':
                if silver < price:
                    real_change = ((change + pkg - 1) // pkg) * pkg
                    update(res+1, n+1, c-1, silver + real_change)
            else:
                assert False

result = 0
for n in range(N+1):
    for c in range(C+1):
        for res in range(N+1):
            if dp[res][n][c] != -1:
                result = max(result, res)
                continue

print(result)
