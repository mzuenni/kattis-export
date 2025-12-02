#!/usr/bin/env python3
import random
import sys

n, hill, s = map(int, sys.argv[1:])
random.seed(s)

a = [[] for _ in range(2)]
for i in range(n):
  a[random.randrange(2)].append(i+1)
a[hill] = a[hill][::-1]

print(n)
print(*a[0], *a[1])
