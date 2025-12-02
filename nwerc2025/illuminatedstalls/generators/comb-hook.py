#!/usr/bin/python3
import sys

n = int(sys.argv[1])
flip = int(sys.argv[2])
squeeze = int(sys.argv[3])

assert n % 2 == 0

print(1)
print(n)

h = (n - 2) // 2

A = 2
B = 5
if squeeze:
    A = 1
    B = 4

if flip:
    print(0, 0, 3 * h + 10, 0)
    print(0, B, 3 * h + 10, B)
    for i in range(2, h + 2):
        if i % 2 == 0:
            print(3 * i, 0, 3 * i, 3)
            print(3 * i - 2, 3, 3 * i + 2, 3)
        else:
            print(3 * i, A, 3 * i, B)
            print(3 * i - 2, A, 3 * i + 2, A)
else:
    print(0, 0, 0, 3 * h + 10)
    print(B, 0, B, 3 * h + 10)
    for i in range(2, h + 2):
        if i % 2 == 0:
            print(0, 3 * i, 3, 3 * i)
            print(3, 3 * i - 2, 3, 3 * i + 2)
        else:
            print(A, 3 * i, B, 3 * i)
            print(A, 3 * i - 2, A, 3 * i + 2)
