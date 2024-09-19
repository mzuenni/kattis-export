#!/usr/bin/env python3
import random
import sys

random.seed(987)

h, w, n = map(int, input().split())

if h*w % n != 0:
    print('impossible')
    sys.exit(0)

block = h*w // n

def area(imin, imax, jmin, jmax):
    return (imax-imin) * (jmax-jmin)

res = [[' '] * w for _ in range(h)]
k = 0
def rec(imin, imax, jmin, jmax):
    global k
    if n*area(imin, imax, jmin, jmax) == h*w:
        for i in range(imin, imax):
            for j in range(jmin, jmax):
                res[i][j] = chr(ord('A') + k)
        k += 1
    else:
        while True:
            if random.randint(0,1):
                if imin+1 == imax: continue
                i = random.randint(imin+1, imax-1)
                if area(imin, i, jmin, jmax)%block == 0:
                    rec(imin, i, jmin, jmax)
                    rec(i, imax, jmin, jmax)
                    return
            else:
                if jmin+1 == jmax: continue
                j = random.randint(jmin+1, jmax-1)
                if area(imin, imax, jmin, j)%block == 0:
                    rec(imin, imax, jmin, j)
                    rec(imin, imax, j, jmax)
                    return

rec(0, h, 0, w)
for row in res:
    print(''.join(row))
