#!/usr/bin/python3

import sys, random
random.seed(sys.argv[1])

es = []
for T in range(2):
    C = 50000//2-1
    #C = 5
    L = 10**8
    at = (L,L)
    if T == 0:
        at = (L, L + 10)
    else:
        at = (L + 10, L)

    def mv(dx,dy,nope=False):
        global at
        if T == 1:
            dx, dy = dy, dx
        to = (at[0]+dx,at[1]+dy)
        if not nope:
            es.append(sorted([list(at),list(to)]))
        at = to
    for i in range(C):
        mv(0,5)
        mv(-2,0,True)
        mv(0,5)
        mv(2,0,True)

    if T == 0:
        at = (L - 2, L + 10)
    else:
        at = (L + 10, L - 2)

    for i in range(C):
        mv(8,0)
        mv(-14,5,True)
        mv(8,0)
        mv(-2,5,True)

    if T == 0:
        at = (L - 8, L - 100)
    else:
        at = (L - 100, L - 8)
    mv(0, 2*L)
    if T == 0:
        at = (L + 6, L + 10)
    else:
        at = (L + 10, L + 6)

    mv(0, L)

if int(sys.argv[1]) != 0:
    i = random.randint(0, len(es)-1)
    while es[i][1][1] - es[i][0][1] + es[i][1][0] - es[i][0][0] != 5:
        i = random.randint(0, len(es)-1)

    if es[i][1][0] == es[i][0][0]:
        es[i][1][1] += 1
    else:
        es[i][1][0] += 1

print(1)
print(len(es))
for u,v in es:
    print(*u,*v)
