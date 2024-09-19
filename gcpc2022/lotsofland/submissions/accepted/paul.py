#!/usr/bin/env python3
import sys

h, w, n = map(int, input().split())
for p in range(1,h+1):
    for q in range(1,w+1):
        if h%p == 0 and w%q == 0 and n*p*q == h*w:
            def col(i,j): return chr(ord('A') + (i//p)*(w//q) + (j//q))
            print('\n'.join(''.join([col(i,j) for j in range(w)]) for i in range(h)))
            sys.exit(0)

print('impossible')
