#!/usr/bin/env python3
grid, (d, h) = [input() for _ in range(7)], map(int, input().split())
print(max(sum(sorted((sum(grid[y][x] == "." for y, c in enumerate(days) if c) for x in range(24)))[-h:]) / h / sum(days)
          for days in __import__("itertools").product((0, 1), repeat=7) if sum(days) >= d))
