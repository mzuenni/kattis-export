#!/usr/bin/python3
import sys

n = int(sys.argv[1])
MAX = int(sys.argv[2])
assert n % 4 == 0

print(1)
print(n)
for x in range(n // 4):
    print(x, 0, x, MAX)
    print(0, x, MAX, x)
    print(MAX - x, 0, MAX - x, MAX)
    print(0, MAX - x, MAX, MAX - x)
