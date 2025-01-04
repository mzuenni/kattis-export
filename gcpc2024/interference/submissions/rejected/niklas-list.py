#!/bin/python3
# @EXPECTED_RESULTS@: TIME_LIMIT_EXCEEDED, RUN_TIME_ERROR

import array

n, w = map(int, input().split())

water = array.array("l", (0 for _ in range(w + 1)))  # Fixed size signed long array
ans = []

for _ in range(n):
    x, *px = input().split()

    if x == "!":  # A new wave!
        p, l, a = map(int, px)

        for i in range(l):
            water[p + i] += [a, 0, -a, 0][i % 4]
    else:  # Query
        pos = int(px[0])
        ans.append(water[pos])

# print(len(ans))
if ans:
    print(*ans, sep="\n")
