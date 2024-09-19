#!/usr/bin/env python3
grid, (d, h), cs = [input() for _ in range(7)], map(int, input().split()), __import__("itertools").combinations
print(max(sum(grid[y][x] == "." for y in v for x in w) / h / d for v in cs(range(7), d) for w in cs(range(24), h)))
