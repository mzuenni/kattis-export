#!/usr/bin/env python3
grid, (d, h) = [input() for _ in range(7)], map(int, input().split())
print(max(sum(sorted(sum(mask & (1 << y) and grid[y][x] == '.' for y in range(7)) for x in range(24))[-h:]) / h / d
          for mask in range(2 ** 7) if bin(mask).count("1") == d))
