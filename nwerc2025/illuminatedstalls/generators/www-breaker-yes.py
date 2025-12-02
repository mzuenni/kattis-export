from random import *
import sys

seed(int(sys.argv[1]))
n = 200000
m = 5*10**8
OFF = m
print(1)
print(n)
segs = []
for i in range(n//2-3):
    segs.append([OFF+-i-1, OFF-m+randint(1,100000), OFF-i-1, OFF+m-randint(1,100000)])
segs.append([0,0,0,1])
segs.append([0,1,1,1])
segs.append([0,0,1,0]) # add a sneaky U here.
for i in range(n//2):
    segs.append([OFF,i+OFF, m+OFF, i+OFF])
shuffle(segs)

if randint(0,1):
    segs = [[s[1],s[0],s[3],s[2]] for s in segs]
for s in segs:
    print(*s)