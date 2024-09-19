#!/usr/bin/env python3
n, m = map(int, input().split())
b = 2*3 + 1
d = [[[1] for _ in range(n)] for __ in range(b)]
base = [0.7, 0.8, 0.9, 1, 1.1, 1.2, 1.3]
for _ in range(m):
    op, i, j = input().split()
    i, j = int(i) - 1, int(j) - 1
    if op == "!":
        for b_itr in range(b):
            while len(d[b_itr][i]) <= len(d[b_itr][j]):
                d[b_itr][i].append(0)
        for b_itr in range(b):
            for k, v in enumerate(d[b_itr][j]):
                d[b_itr][i][k + 1] += v * base[b_itr]**k
        # print(f"replace d[{i}] with {d[i]}")
    else:
        # print(f"compare d[{i}] with d[{j}]:\n{d[i]}\n{d[j]}")
        cnt = 0
        for b_itr in range(b):
            if d[b_itr][i] == d[b_itr][j]:
                continue
            elif len(d[b_itr][i]) > len(d[b_itr][j]):
                cnt += 1
            elif len(d[b_itr][i]) < len(d[b_itr][j]):
                cnt -= 1
            else:
                for k in range(len(d[b_itr][i]) - 1, -1, -1):
                    if d[b_itr][i][k] > d[b_itr][j][k]:
                        cnt += 1
                        break
                    elif d[b_itr][i][k] < d[b_itr][j][k]:
                        cnt -= 1
                        break
                assert k != -1
        if cnt < 0:
            print("<")
        elif cnt > 0:
            print(">")
        else:
            print("=")
