#find the MST, check whether MST is really a tree and not a forest, check the weight of the MST not greater than available material
#using prim with heapqueue


#off by one error: do accept even if the needed length greater than the available by one

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
for i in range(m):
    s, t, w = list(map(int, input().split()))
    graph[s-1].append((t-1,w))
    graph[t-1].append((s-1,w))
    if i<l:
        available+=w
        
weight, cnt=prim(graph)

if cnt==n and weight<=available+1: #SHOULD BE weight<=available
    print("possible")
else:
    print("impossible")
    
