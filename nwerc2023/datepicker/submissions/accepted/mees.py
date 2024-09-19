#!/usr/bin/python3

calendar = [input() for _ in range(7)]
d, h = [int(x) for x in input().split()]

best = 0.0
for day_mask in range(2**7):
    if sum((day_mask >> i) & 1 for i in range(7)) != d:
        continue
    hour_counts = []
    for hour in range(24):
        hour_counts.append(sum(1 if calendar[i][hour] == '.' else 0 for i in range(7) if (day_mask & (2**i)) > 0))
    hour_counts.sort(reverse=True)
    best = max(best, sum(hour_counts[:h]) / (h * d))

print(best)
