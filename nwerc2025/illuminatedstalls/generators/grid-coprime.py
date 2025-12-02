#!/usr/bin/python3
import sys

n = int(sys.argv[1])
MAX = int(sys.argv[2])
assert n % 4 == 0

c1 = n // 2 + 1
c2 = n // 2 + 3

print(1)
print(n)

for i in range(c1 - 2):
    print(0, c2 * i, MAX, c2 * i)
for i in range(c2 - 2):
    print(c1 * i, 0, c1 * i, MAX)
