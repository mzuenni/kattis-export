#!/usr/bin/env python3
import random
import sys

nmin, nmax, s = map(int, sys.argv[1:])
random.seed(s)

n = random.randint(nmin, nmax)
print(n)
print(*random.sample(range(1, n+1), n))
