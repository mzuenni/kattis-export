#
#(flawed) idea:
#for a<->b the network would look like
#
#  source---degree(a) ---> a_out -> b_in -- d-->sink
#  source---degree(b) ---> b_out -> a_in -- d-->sink
#
# The test for d is considered as passed if max_flow>=edge_cnt (uses edmonds-karp for max flow)
#
# Do binary search for find the minimal d
#
# The main problem of this reduction is that one edge can contribute twice (a->b and b->a) to the flow, the is no guarantee that it used only once
#
#
# This implementation has also other problems: wrong handling of multi edges and too slow
#
#
from collections import deque as Queue

def bfs(graph, start, end):
    n=len(graph)
    preds=[-1]*n
    q=Queue()
    preds[start]=start
    q.append(start)
    while q:
        cur=q.popleft()
        for next in list(graph[cur].keys()):
            if preds[next]==-1:
                preds[next]=cur
                if(next==end):
                    return preds
                else:
                    q.append(next)
    return None
                    
                    
def add_flow(graph, end, preds):
    #skip finding minimum -> it is mostly 1 (if there are no multi edges)
    while preds[end]!=end:
        next=preds[end]   
        if graph[next][end]==1:
            del(graph[next][end])
        else:
            graph[next][end]-=1          
        newVal=graph[end].get(next,0)+1
        graph[end][next]=newVal
        end=next
        
        
def edmonds_karp(graph, start, end):
    cnt=0
    while True:
        preds=bfs(graph, start, end)
        if preds is None:
            return cnt
        add_flow(graph, end, preds)
        cnt+=1
          
        

def construct_graph(n, edge_list, cnts, b):
    graph=[{} for _ in range(2*n+2)]
    
    for edge in edge_list:
        graph[edge[0]][n+edge[1]]=1
        graph[edge[1]][n+edge[0]]=1
    
    for i, cnt in enumerate(cnts):
        graph[2*n][i]=cnt
        graph[n+i][2*n+1]=min(b, cnt)
       
    return graph
   
#main:
n=int(input())
m=int(input())
edge_list=[]
cnts=[0]*n

for _ in range(m):
    edge=[x-1 for x in map(int, input().split())]
    cnts[edge[0]]+=1
    cnts[edge[1]]+=1
    edge_list.append(edge)
    
must_have=sum(cnts)/2

#do binary search
upper=max(cnts)
lower=0
while(lower+1<upper):
    middle=(lower+upper)/2
    graph=construct_graph(n, edge_list, cnts, middle)
    if edmonds_karp(graph, 2*n, 2*n+1)>=must_have:
        upper=middle
    else:
        lower=middle
        
print(upper)

