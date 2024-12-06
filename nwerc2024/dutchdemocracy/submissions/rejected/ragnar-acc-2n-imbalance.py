#!/usr/bin/env python3
# @EXPECTED_RESULTS@: RUN_TIME_ERROR, TIME_LIMIT_EXCEEDED

from bisect import bisect_left

n = int(input())
a = list(reversed(sorted(map(int, input().split()))))
t = sum(a) // 2 + 1

L = n // 2 + 1
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

sums = [0] * (sum(a) + 2)
for ls in lsums:
    sums[ls + 1] += 1
for i in range(sum(a)):
    sums[i + 1] += sums[i]

rsums = [0]
for i in range(R):
    ai = a[L + i]
    for sr in rsums:
        # We want t-ai <= s=sl+sr < t
        # so t-ai-sr <= sl < t-sr
        h = sums[max(t - sr, 0)]
        l = sums[max(t - sr - ai, 0)]
        ans += h - l
    newsums = [x + ai for x in rsums]
    rsums.extend(newsums)

print(ans)
