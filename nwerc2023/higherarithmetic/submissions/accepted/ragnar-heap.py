#!/usr/bin/env python3
import heapq

n = int(input())
a = list(map(lambda x: (int(x), int(x)), input().split()))
heapq.heapify(a)
ones = 0
while len(a) > 0 and a[0][0] == 1:
    ones += 1
    heapq.heappop(a)
for _ in range(ones):
    if len(a) > 0 and a[0][0] < 3:
        x, x0 = heapq.heappop(a)
        heapq.heappush(a, (x + 1, x0))
    else:
        heapq.heappush(a, (1, 1))
if len(a) > 1 and a[0][0] == 1:
    heapq.heappop(a)
    x, x0 = heapq.heappop(a)
    heapq.heappush(a, (x + 1, x0))


def term(x, x0):
    return "(" + "+".join([str(x0)] + ["1"] * (x - x0)) + ")"


print("*".join(term(x, x0) for x, x0 in a))
