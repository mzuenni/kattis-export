#!/usr/bin/env python3

import sys
import random

MAX_YEAR = int(1e9)

assert len(sys.argv) == 3, "Usage: rand.py seed n"
random.seed(sys.argv[1])
n = int(sys.argv[2])

a_years = set()
print(n)
for _ in range(n):
    a = random.randint(1, MAX_YEAR)
    while a in a_years:
        a = random.randint(1, MAX_YEAR)

    a_years.add(a)

    print(a, a)
