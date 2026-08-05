# translation of egor_edmonds_kapr.cpp to python
#
# This is a pretty slow version:
#      it uses map to store edges instead of remembering the backward edge for every edge
#      it does not try to choose the direction of an edge, takes it as it comes
#      it does not try to calculate a better upper limit as n for d 
#
#

from collections import deque as Queue


MAX=2000000000

def bfs(graph, start, end):
    n=len(graph)
    preds=[(-1, MAX)]*n
    q=Queue()
    
    preds[start]=(-2, MAX)
    q.append(start)
    while q:
        cur=q.popleft()
        for next, cap in list(graph[cur].items()):
            if preds[next][0]==-1:
                preds[next]=(cur, min(preds[cur][1], cap))
                q.append(next)
                if next==end:
                    return preds
    return None
   
   

def add_flow(graph, end, preds):
    diff=preds[end][1]
    while True:
        if preds[end][0]==-2:
            break
        next=preds[end][0]
        adjusted_cap=graph[next][end]-diff;
        if adjusted_cap:
            graph[next][end]=adjusted_cap
        else:
            del(graph[next][end])
        graph[end][next]=diff+graph[end].get(next, 0)
        end=next
        
    return diff
    
def edmonds_karp(graph, start, end):
    flow=0 
    while True:
        preds=bfs(graph, start, end)
        if preds is None:
            break     
        flow+=add_flow(graph, end, preds)
    return flow

 

def init_graph(node_cnt, edges, d):  
    n=2*node_cnt+2
    graph=[dict() for _ in range(n)]
    cnts=[0]*n
    for edge in edges:
        cnts[edge[0]]+=1
        graph[edge[0]][edge[1]]= 1
    
    expected=0
    for i in range(n-2):
        if cnts[i]>d:
            needed=cnts[i]-d
            graph[n-2][i]=needed
            expected+=needed
        if cnts[i]<d:
            graph[i][n-1]=d-cnts[i]
 
    return (expected, graph, n-2, n-1)

#main:
n,m=list(map(int, [input(), input()]))
edges=[]
for _ in range(m):
    edges.append([x-1 for x in map(int, input().split())])
  

lower=0
upper=min(n,m)
    
while lower+1<upper:
    middle=(lower+upper)//2;
    expected, graph, source, target=init_graph(n, edges, middle)
    received=edmonds_karp(graph, source, target)
    if expected==received:
        upper=middle
    else:
        lower=middle

print(upper)


