#!/usr/bin/env python3
import random
import sys

n, s = map(int, sys.argv[1:])
random.seed(s)

a = list(range(1, n+1))
for _ in range(random.randint(1, 1 + n//3)):
  k = random.randint(2, 5)
  i = random.randrange(1, k)
  j = random.randint(0, n-k)
  a[j:j+k] = a[j+i:j+k] + a[j:j+i]

print(n)
print(*a)
