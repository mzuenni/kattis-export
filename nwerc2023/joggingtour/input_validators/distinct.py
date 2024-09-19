#!/usr/bin/env python3
import sys

n = int(input())
pts = set()
for i in range(n):
    [x,y] = input().split(' ')
    p = (int(x),int(y))
    if p in pts:
        print('Two bakeries at', p)
        sys.exit(1)
    pts.add(p)
sys.exit(42)
