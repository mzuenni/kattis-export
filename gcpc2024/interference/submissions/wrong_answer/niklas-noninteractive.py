#!/bin/python3

n, w = map(int, input().split())

waves = []  # position, length, amplitude
queries = []  # position
ans = []

for _ in range(n):
    x, *p = input().split()

    if x == "!":  # A new wave!
        waves.append(tuple(map(int, p)))
    else:  # Query
        queries.append(int(p[0]))

for pos in queries:
    ans.append(
        sum([a, 0, -a, 0][(pos - p) % 4] for p, l, a in waves if p < pos < p + l)
    )

# print(len(ans))
if ans:
    print(*ans, sep="\n")
