#!/usr/bin/env python3

n, counts = int(input()), __import__("collections").defaultdict(lambda: [0] * 10)
for _ in range(n):
    for i, s in enumerate(input().strip().split()): counts[s][i] += 1
counts = sorted(counts.items(), key=lambda x: (sum(x[1]), x[1]))
print("tie" if len(counts) > 1 and counts[-1][1] == counts[-2][1] else counts[-1][0])
