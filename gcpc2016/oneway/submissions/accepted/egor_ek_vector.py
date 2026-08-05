# translation of egor_ek_vector.cpp to python, max flow with edmonds karp

from collections import deque as Queue
from collections import namedtuple

#CapEdge = namedtuple('CapEdge', 'target reverse_edge cap')
WayEdge = namedtuple('WayEdge', 'reverse_edge min_cap')

MAX=2000000000

def bfs(graph, start, end):
    n=len(graph)
    preds=[(MAX, MAX)]*n
    q=Queue()
    
    preds[start]=WayEdge(2*MAX, MAX)
    q.append(start)
    while q:
        cur=q.popleft()
        for edge in graph[cur]:
            if edge[2]>0 and preds[edge[0]][0]==MAX:
                preds[edge[0]]=WayEdge(edge[1], min(preds[cur][1], edge[2]))
                q.append(edge[0])
                if edge[0]==end:
                    return preds
    return None
   
   

def add_flow(graph, end, preds):
    diff=preds[end].min_cap;
    while True:
        if preds[end].min_cap==MAX:
            break
        back_edge=graph[end][preds[end].reverse_edge]
        edge=graph[back_edge[0]][back_edge[1]]
        edge[2]-=diff
        back_edge[2]+=diff
        end=back_edge[0]
    return diff
    
def edmonds_karp(graph, start, end):
    flow=0 
    while True:
        preds=bfs(graph, start, end)
        if preds is None:
            break     
        flow+=add_flow(graph, end, preds)
    return flow

 
def add_edge(graph, start, end, cap):
    edge=[end, len(graph[end]), cap]
    rev_edge=[start, len(graph[start]), 0]
    graph[start].append(edge)
    graph[end].append(rev_edge)


def init_graph(node_cnt, edges, d):  
    n=2*node_cnt+2
    graph=[list() for _ in range(n)]
    cnts=[0]*n
    for edge in edges:
        if cnts[edge[0]]<cnts[edge[1]]:
            cnts[edge[0]]+=1
            add_edge(graph, edge[0], edge[1], 1)
        else:
            cnts[edge[1]]+=1
            add_edge(graph, edge[1], edge[0], 1)
    
    expected=0
    for i in range(n-2):
        if cnts[i]>d:
            needed=cnts[i]-d
            add_edge(graph, n-2, i, needed)
            expected+=needed
        if cnts[i]<d:
            add_edge(graph, i, n-1, d-cnts[i])
 
    return (expected, graph, n-2, n-1)


def estimate_max_d(edges, n):
    cnts=[0]*n
    for edge in edges:
         if cnts[edge[0]]<cnts[edge[0]]:
             cnts[edge[0]]+=1
         else:
             cnts[edge[1]]+=1
    return max(cnts)

#main:
n,m=list(map(int, [input(), input()]))
edges=[]
for _ in range(m):
    edges.append([x-1 for x in map(int, input().split())])
  

lower=0
upper=estimate_max_d(edges, n)
    
while lower+1<upper:
    middle=(lower+upper)//2;
    expected, graph, source, target=init_graph(n, edges, middle)
    received=edmonds_karp(graph, source, target)
    if expected==received:
        upper=middle
    else:
        lower=middle

print(upper)


