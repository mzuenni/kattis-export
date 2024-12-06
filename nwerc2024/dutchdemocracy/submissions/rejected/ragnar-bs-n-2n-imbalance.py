#!/usr/bin/env python3
# @EXPECTED_RESULTS@: TIME_LIMIT_EXCEEDED, RUN_TIME_ERROR

from bisect import bisect_left

n = int(input())
a = list(reversed(sorted(map(int, input().split()))))
t = sum(a) // 2 + 1

L = min(n // 2 + 1, n)
R = n - L
lsums = [0]
ans = 0
for i in range(L):
    ai = a[i]
    for s in lsums:
        if s < t and s + ai >= t:
            ans += 1
    newsums = [x + ai for x in lsums]
    lsums.extend(newsums)

lsums.sort()

rsums = [0]
for i in range(R):
    ai = a[L + i]
    for sr in rsums:
        # We want t-ai <= s=sl+sr < t
        # so t-ai-sr <= sl < t-sr
        h = bisect_left(lsums, t - sr)
        l = bisect_left(lsums, t - sr - ai)
        ans += h - l
    newsums = [x + ai for x in rsums]
    rsums.extend(newsums)

print(ans)
