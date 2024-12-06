#!/usr/bin/env python3

def modexp(a,b,n):
    if b==0: return 1
    elif b==1: return a%n
    elif b%2:
        return (a*modexp((a*a)%n,b//2,n))%n
    else: return modexp((a*a)%n,b//2,n)

n, k = [int(x) for x in input().split()]
s = input()
expk = modexp(2,k,n)
idxs = [(expk*i)%n for i in range(n)]
print("".join([s[i] for i in idxs]))
