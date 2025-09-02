#!/usr/bin/env python

t,p = map(int, raw_input().split())
st,sp = (map(float, raw_input().split()) for i in '00')

def score_distribution(strength):
    solved = 0
    chances = []
    l = raw_input().split()
    for i in filter(lambda x: l[x] <> '-', range(p)):
        chances += [1.0 if l[i] == 'X' else strength * sp[i]]

    dp = [[1.0 if i == 0 else 0.0 for i in range(p+1)]]
    for i in range(len(chances)):
        dp += [[0 for _ in range(p+1)]]
        for j in range(p+1):
            if dp[i][j] > 0:
                dp[i+1][j+1] += dp[i][j] * (0 + chances[i])
                dp[i+1][j+0] += dp[i][j] * (1 - chances[i])

    return dp[-1]

players = map(score_distribution, st)
score = sum(map(lambda x: 1 if x == 'X' else 0, raw_input().split()))

pwin = 1.0
for i in players:
    pwin *= (1 - sum(i[score+1:]))

print '%.8f' % (pwin)
