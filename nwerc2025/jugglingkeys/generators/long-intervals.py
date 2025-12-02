#!/usr/bin/env python3
import random
import sys

s = int(sys.argv[1])
k = int(sys.argv[2])
random.seed(s)

n = 10**5
x = 10**9
ps = [random.sample(range(n), n) for _ in range(3)]
print(n, k, n)
for i in range(n):
  print(ps[0][i]+1, ps[1][i], x-ps[2][i])
