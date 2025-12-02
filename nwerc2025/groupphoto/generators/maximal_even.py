#!/usr/bin/python3
import sys

s = int(sys.argv[1])
n = 2 * s
print(n)

p = [n - 1, 1, n // 2 + 1] + [j for j in range(2, n - 1) if j != n // 2 + 1] + [n]

print(*p)
