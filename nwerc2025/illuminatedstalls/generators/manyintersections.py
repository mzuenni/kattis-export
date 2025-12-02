#!/usr/bin/python3
import sys

n = int(sys.argv[1])
A = int(sys.argv[2])
B = int(sys.argv[3])
LIM = 10**9
t = 200000//n
print(t)
for _ in range(t):
    print(n)

    for i in range(n//2):
        print(0,A*(i+1),(n+1)//2*B,A*(i+1))
    for j in range(n-n//2):
        print(B*(j+1),0,B*(j+1),n//2*A)
