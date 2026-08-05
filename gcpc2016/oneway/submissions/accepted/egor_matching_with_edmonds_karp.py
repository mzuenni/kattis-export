# translation of egor_matching_as_maxflow.cpp to python (uses edmonds karp as max flow algorithmus)
#
# however this version is slower, because it uses maps instead of remembering the backward edge
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
    m=len(edges)  
    n=len(edges)+2*node_cnt+2
    graph=[dict() for _ in range(n)]

    for i,edge in enumerate(edges):
        graph[i][m+edge[0]]=1
        graph[i][m+edge[1]]=1
    
    for i in range(m):
        graph[n-2][i]=1
        
    for i in range(m,n-2):
        graph[i][n-1]=d
 
    return (graph, n-2, n-1)

#main:
n,m=list(map(int, [input(), input()]))
edges=[]
for _ in range(m):
    edges.append([x-1 for x in map(int, input().split())])
  

lower=0
upper=min(n,m)
    
while lower+1<upper:
    middle=(lower+upper)//2;
    graph, source, target=init_graph(n, edges, middle)
    if edmonds_karp(graph, source, target)==m:
        upper=middle
    else:
        lower=middle

print(upper)


