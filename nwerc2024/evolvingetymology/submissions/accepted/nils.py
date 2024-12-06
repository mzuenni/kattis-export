#!/usr/bin/env python3
n,k = map(int,input().split())
s = input()
mul = pow(2,k,n)
print("".join([s[(i*mul)%n] for i in range(n)]))
