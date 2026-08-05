#find the MST, check whether MST is really a tree and not a forest, check the weight of the MST not greater than available material
#using prim with heapqueue

#however, it does not consider, that there could be multi edges and takes the one which comes last

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
        for next, weight in list(graph[cur].items()):
            if weight<weights[next] and not used[next]:
                weights[next]=weight
                heappush(q,(weight, next))
                
    return (W, CNT)
 

#main
n, m, l = list(map(int, input().split()))

graph=[{} for _ in range(n)]
available=0
for i in range(m):
    s, t, w = list(map(int, input().split()))
    graph[s-1][t-1]=w #HERE WE GO: what if there was a shorter edge?
    graph[t-1][s-1]=w #HERE WE GO: what if there was a shorter edge?
    if i<l:
        available+=w
        
weight, cnt=prim(graph)

if cnt==n and weight<=available:
    print("possible")
else:
    print("impossible")
    
