#!/usr/bin/python3
C = 50000-1
# C = 20
es = []
L = 10**8
at = (L,L)
def mv(dx,dy,nope=False):
    global at
    to = (at[0]+dx,at[1]+dy)
    if not nope:
        es.append(sorted((at,to)))
    at = to
for i in range(C):
    mv(0,5)
    mv(-2,0,True)
    mv(0,5)
    mv(2,0,True)
at = (L-2,L)
for i in range(C):
    mv(8,0)
    mv(-14,5,True)
    mv(8,0)
    mv(-2,5,True)

at = (L-8,L)
mv(0,L)
at = (L+6,L)
mv(0,L)
print(1)
print(len(es))
for u,v in es:
    print(*u,*v)