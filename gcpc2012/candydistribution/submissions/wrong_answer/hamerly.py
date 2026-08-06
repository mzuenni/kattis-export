#!/usr/bin/env python3

import sys
import math

n = int(sys.stdin.readline())
for _ in range(n):
    k, c = map(int, sys.stdin.readline().split())
    ans = (k + 1) // c
    if ans * c <= k:
        ans += 1
    print(ans)
