#find the MST, check whether MST is really a tree and not a forest, check the weight of the MST not greater than available material
#using prim with heapqueue

#this is a try to estimate how good the test case set is for bigger number of edges.
#a combined strategy: 1. for less than 1000 edges: run prim
#                     2. for more than 1000 edges take 100 edges, sort them, find the average of 1.2*100*n/m smallest edges, average*(n-1) is #                        the estimation of MST weight (factor 1.2 accounts for the fact, that we just cannot take the best for MST)

max_val=10**9

#returns the number of nodes in the tree and its weight
from heapq import *#priority queue   
def prim(graph):    
    n=len(graph)    
    W, CNT = 0,0
    weights=[max_val]*n
    used=[False]*n#for locking the parents
    
    q=[] 
    root=0  
    heappush(q,(0, root))
    weights[root]=0
    used[root]=True
    
    while q:
        w, cur=heappop(q)
        if weights[cur]<w:
            continue
        else:
            used[cur]=True
            W+=w
            CNT+=1        
        for next, weight in graph[cur]:
            if weight<weights[next] and not used[next]:
                weights[next]=weight
                heappush(q,(weight, next))
                
    return (W, CNT)
 

#main
n, m, l = list(map(int, input().split()))

graph=[[] for _ in range(n)]
available=0
weights=[0]*m
for i in range(m):
    s, t, w = list(map(int, input().split()))
    graph[s-1].append((t-1,w))
    graph[t-1].append((s-1,w))
    weights[i]=w
    if i<l:
        available+=w
 
if m< 1000:        
    weight, cnt=prim(graph)

    if cnt==n and weight<=available:
        print("possible")
    else:
        print("impossible")
        
else:
    step=m/100
    samples=weights[::100]
    weights.sort()
    k=min(100.0, 120.0*n/m)
    expected=(n-1)*sum(weights[:int(k+1)])/k
    print("possible" if expected<=available else "impossible")
    
