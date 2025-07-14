from heapq import heappop, heappush

n, m, vil, k = map(int, input().split())
a = [-1] * n
a2 = [0] * (vil + 1)

for i, x in enumerate([*map(int, input().split())]):
    a2[i+1] = a2[i] + x
    for j in range(x):
        a[a2[i] + j] = i

g = [[] for i in range(n)]
connecting = [-1] * vil
for i in range(m):
    u, v, w = map(int, input().split())
    u -= 1
    v -= 1
    if u > v:
        u, v = v, u

    if a[u] != a[v]:
        if u == 0 and v == n-1:
            connecting[-1] = w
        else:
            connecting[a[u]] = w
    else:
        g[u].append((v, w))
        g[v].append((u, w))

term = [False] * n
cnt = [0] * vil
for u in [*map(int, input().split())]:
    u -= 1
    term[u] = True
    cnt[a[u]] += 1

dp2 = []
for village in range(vil):
    offset = a2[village]
    N = a2[village+1] - offset
    if N == 1:
        dp2.append((0, 0, 0, 0, 0))
        continue

    t = [0, N-1]
    for i in range(1, N-1):
        if term[offset + i]:
            t.append(i)

    k = len(t)

    dp = [10**18] * (N << k)
    for i in range(k):
        dp[(t[i] << k) + (1<<i)] = 0
    for i in range(N):
        dp[i << k] = 0

    for msk in range(1, 1<<k):
        for i in range(N):
            msk2 = msk
            while msk2 > 0:
                dp[(i << k) + msk] = min(dp[(i << k) + msk], dp[(i << k) + msk2] + dp[(i << k) + (msk^msk2)])
                msk2 = (msk2-1) & msk

        q = []
        for i in range(N):
            heappush(q, dp[(i << k) + msk] * n + i)

        while len(q) > 0:
            val = heappop(q)
            u = val % n
            val //= n
            if dp[(u << k) + msk] != val:
                continue

            for v, w in g[offset + u]:
                v -= offset
                if dp[(v << k) + msk] > dp[(u << k) + msk] + w:
                    dp[(v << k) + msk] = dp[(u << k) + msk] + w
                    heappush(q, dp[(v << k) + msk] * n + v)

    sup = (1<<k) - 1
    sup2 = sup
    sup3 = sup
    sup4 = sup
    if not term[offset + 0]:
        sup3 ^= 1
        sup4 ^= 1
    if not term[offset + N - 1]:
        sup2 ^= 2
        sup4 ^= 2


    x = 0
    for i in range(k):
        if sup4 >> i & 1:
            x = dp[(t[i] << k) + sup4]

    y = 10**18
    for i in range(1, 1<<k, 4):
        y = min(y, dp[i] + dp[((N-1) << k) + (sup ^ i)])

    dp2.append((dp[sup], dp[sup2], dp[((N-1) << k) + sup3], x, y))

pref = [0] * (3*vil + 1)
for i in range(3*vil):
    pref[i+1] = pref[i] + dp2[i%vil][0]

ans = 10**18
sm = sum(connecting)
l = 0
while l < vil:
    r = l+1
    c = sm - connecting[l]
    while cnt[r % vil] == 0:
        c -= connecting[r % vil]
        r += 1

    if r == l+vil:
        ans = min(ans, dp2[r % vil][3])
    else:
        c += dp2[l][1] + dp2[r%vil][2]
        c += pref[l+vil] - pref[r+1]
        ans = min(ans, c)

    ans = min(ans, dp2[l][4] + sm + pref[l+vil] - pref[l+1])
    
    l = r

print(ans)
