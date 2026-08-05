# this is a translation of EgorDP.py to python

from heapq import *

MAX_VAL=float("inf")

def getMinDists(gs, MAX):
    q=[]
    dists=[MAX_VAL]*MAX  

    heappush(q, (0,0))
    dists[0]=0
    while q:
        d, i=heappop(q)
        if d!=dists[i]:
            continue
        for edge in gs:
            next=(edge+i)%MAX
            nextDist=d+edge
            if dists[next]>nextDist:
                dists[next]=nextDist
                heappush(q,(nextDist, next))
                
    return dists
	

N,K=list(map(int, input().split()))
gs=list(map(int, input().split()))

MAX=gs[0]
gs=gs[1:]

minDists=getMinDists(gs, MAX)
index=K%MAX

print("possible" if minDists[index]<=K else "impossible")   



