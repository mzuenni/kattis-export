#!/usr/bin/env python3
import random
import sys

i = int(sys.argv[1])
j = int(sys.argv[2])

M = 10
a = ["a" for i in range(M)]
b = ["b" for i in range(M)]
a[i] = 'x'
b[j] = 'x'
print(2)
print(*a)
print(*b)

