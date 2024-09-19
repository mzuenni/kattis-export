#!/usr/bin/env python3
n, m = map(int, input().split())
d = [[1] for _ in range(n)]
for _ in range(m):
    op, i, j = input().split()
    i, j = int(i) - 1, int(j) - 1
    if op == "!":
        while len(d[i]) <= len(d[j]):
            d[i].append(0)
        for k, v in enumerate(d[j]):
            d[i][k + 1] += v
        # print(f"replace d[{i}] with {d[i]}")
    else:
        # print(f"compare d[{i}] with d[{j}]:\n{d[i]}\n{d[j]}")
        if d[i] == d[j]:
            print("=")
            continue
        elif len(d[i]) > len(d[j]):
            print(">")
        elif len(d[i]) < len(d[j]):
            print("<")
        else:
            for k in range(len(d[i]) - 1, -1, -1):
                if d[i][k] > d[j][k]:
                    print(">")
                    break
                elif d[i][k] < d[j][k]:
                    print("<")
                    break
            assert k != -1
