#!/bin/python3

n, w = map(int, input().split())

waves = []  # position, length, amplitude
ans = []

for _ in range(n):
    x, *p = input().split()

    if x == "!":  # A new wave!
        waves.append(tuple(map(int, p)))
    else:  # Query
        pos = int(p[0])
        ans.append(
            sum(
                [a, 0, -a, 0][(pos - p) % 4]
                for p, l, a in waves
                if p < pos < p + l
            )
        )

# print(len(ans))
if ans:
    print(*ans, sep="\n")
