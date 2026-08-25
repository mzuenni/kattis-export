# this is a translation of Egor_GGT4Large.java to python

from math import gcd

def bruteForce(gs, K):
    reachable=[True]+[False]*K
    for g in gs:
        for i in range(K+1):
            if reachable[i] and i+g<=K:
                reachable[i+g]=True
    return reachable[K]

def withGCD(gs, K):
   ggt=gs[0]
   for g in gs[1:]:
        ggt=gcd(ggt, g)
   return K%ggt==0
    
    	
N,K=list(map(int, input().split()))
gs=list(map(int, input().split()))

loot = bruteForce(gs, K) if K<10**6 else withGCD(gs, K)

print("possible" if loot else "impossible") 

