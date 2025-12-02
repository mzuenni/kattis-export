#!/usr/bin/env python3
n = int(input())

counts = dict()
for _ in range(n):
    ss = list(input().strip().split())
    for i in range(0, 10):
        s = ss[i]
        if s not in counts:
            counts[s] = [0]*10
        counts[s][i] += 1
counts = list(counts.items())
counts.sort(key=lambda x: (sum(x[1]), x[1]))
if len(counts) > 1 and counts[-1][1] == counts[-2][1]:
    print('tie')
else:
    print(counts[-1][0])
