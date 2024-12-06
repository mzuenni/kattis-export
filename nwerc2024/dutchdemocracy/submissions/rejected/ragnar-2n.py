#!/usr/bin/env python3
# @EXPECTED_RESULTS@: RUN_TIME_ERROR, TIME_LIMIT_EXCEEDED

n = int(input())
a = list(reversed(sorted(map(int, input().split()))))
t = sum(a) // 2 + 1

L = n
lsums = [0]
ans = 0
for i in range(L):
    ai = a[i]
    for s in lsums:
        if s < t and s + ai >= t:
            ans += 1
    newsums = [x + ai for x in lsums]
    lsums.extend(newsums)

print(ans)
