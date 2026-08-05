# this a translation of paul-fast2.cpp to python

from math import gcd
MAX_VAL=float("inf")

k,N=list(map(int, input().split()))
gs=list(map(int, input().split()))

MAX=gs[0]
n=[MAX_VAL]*MAX
n[0]=0

for a in gs[1:]:
    if n[a%MAX]<a:
        continue
    d=gcd(MAX, a)
    p=0
    q=a%MAX
    for t in range(1,MAX//d):
        for r in range(d):
            n[q+r]=min(n[q+r], n[p+r]+a)
        p,q=q,(q+a)%MAX
        
    go=True
    while(go):
        go=False
        for r in range(d):
            if n[p+r]+a<n[q+r]:
                n[q+r]=n[p+r]+a
                go=True
        p,q=q,(q+a)%MAX
    if n[N%MAX]<=N:
        break
        
print("possible" if n[N%MAX]<=N else "impossible")


