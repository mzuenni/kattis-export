#!/usr/bin/env python3# @EXPECTED_RESULTS@: ACCEPTED, RUNTIME_ERROR, TIME_LIMIT_EXCEEDED


import bisect
import sys
from math import factorial
from itertools import permutations

MOD = 998244353
n = int(input())
cards = [tuple(map(int, input().strip().split())) for _ in range(n)]


def simulate(order):
    timeline = []
    for a, b in order:
        left_index = bisect.bisect_right(timeline, min(a, b))
        right_index = bisect.bisect_left(timeline, max(a, b))
        if left_index == right_index:
            bisect.insort(timeline, a)
    return len(timeline)


results = [simulate(order) for order in permutations(cards)]
assert len(results) == factorial(n)
s = sum(results)
if n <= 8:
    print("Readable answer:", s / len(results), file=sys.stderr)
print(((s % MOD) * pow(len(results), -1, MOD)) % MOD)
