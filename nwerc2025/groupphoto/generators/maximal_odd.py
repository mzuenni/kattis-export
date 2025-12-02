#!/usr/bin/python3
import sys

s = int(sys.argv[1])
n = 2 * s - 1
print(n)

p = list(reversed(range(1, n))) + [n]

print(*p)
