#!/usr/bin/python3
import sys

n = int(sys.argv[1])
flip = int(sys.argv[2])

print(1)
print(n)

if flip:
    print(0, 0, 2 * n, 0)
    print(0, 3, 2 * n, 3)
    for i in range(n - 2):
        if i % 2 == 0:
            print(2 * i, 0, 2 * i, 2)
        else:
            print(2 * i, 1, 2 * i, 3)
else:
    print(0, 0, 0, 2 * n)
    print(3, 0, 3, 2 * n)
    for i in range(n - 2):
        if i % 2 == 0:
            print(0, 2 * i, 2, 2 * i)
        else:
            print(1, 2 * i, 3, 2 * i)
