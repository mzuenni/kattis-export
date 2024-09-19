#!/usr/bin/env python3
"""
Solves the problem in O(m * n).

author: Lucas Alber
"""
import sys

N, M = [int(x) for x in sys.stdin.readline().strip().split()]
costs = [0] + [1 << 63 for _ in range(N)]

for i in range(1, N + 1):
    cost, *values = [int(x) for x in sys.stdin.readline().strip().split()]
    for j in range(min(M, N - i + 1)):
        costs[i + j] = min(costs[i + j], costs[i - 1] + cost - values[j])

print(costs[N])
