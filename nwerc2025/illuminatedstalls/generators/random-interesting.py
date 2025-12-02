#!/usr/bin/env pypy3
from random import randint, seed
import sys

n,A = map(int,sys.argv[1:3])
seed(int(sys.argv[3]))

SM_N = 2 * 10 ** 5

print(SM_N // n)
for IT in range(SM_N // n):
    def segment():
        x,y = randint(0,A),randint(0,A)
        while True:
            x2,y2 = randint(0,A),randint(0,A)
            if (x2==x) + (y2==y) == 1:
                return sorted(((x,y),(x2,y2)))
    s = []

    def inter(a,b,c,d):
        same = ((a[0]==b[0]) == (c[0]==d[0]))*1000
        if max(a[0],c[0])<=min(b[0],d[0]) and max(a[1],c[1])<=min(b[1],d[1]):
            return same+1
        return 0
        
    curinter = 0
    for x in range(1,n+1):
        while True:
            a,b = segment()
            mine = 0
            for c,d in s:
                mine+=inter(a,b,c,d)
            if mine+curinter<3*x:
                s.append((a,b))
                break

    print(n)
    for a,b in s:
        print(*a,*b)
