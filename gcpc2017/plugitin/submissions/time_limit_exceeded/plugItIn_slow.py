'''
Created on 12.05.2017

@author: Moritz Fuchs
'''

from collections import defaultdict
from copy import deepcopy

def bfs(start, graph):
    parents = defaultdict(lambda:-1)
    seen = set()
    q = [start]
    
    while q:
        c = q.pop(0)
        if not c in seen:
            seen.add(c)
            for n in graph[c]:
                    if not n in seen:
                        parents[n] = c
                        q.append(n)
    return parents

def flow(graph, sink, flow_init=0):
    f = flow_init
    parents = bfs(0, graph)
    
    while parents[sink] != -1:
        #augment
        current = sink
        prev = parents[current]
        while prev != -1:
            #reverse edges
            graph[prev].remove(current)
            graph[current].add(prev)
            current = prev
            prev = parents[current]
        f += 1
        parents = bfs(0, graph)
        
    return graph, f

def copyVertex(graph, v, index, source, sink):
    ng = deepcopy(graph)
    for n in graph[v]:
        ng[index].add(n)
        ng[index+1].add(n)

        ng[source].add(index)
        ng[source].add(index+1)
        
    return ng

m,n,k = list(map(int, input().split()))

# setup graph
graph = defaultdict(lambda:set())

source = 0
offset_right = m
sink = n+m+10
for _ in range(k):
    start, end = list(map(int, input().split()))
    #source
    graph[source].add(start)
    #edge to be covered
    graph[start].add(offset_right + end)
    #sink
    graph[offset_right+end].add(sink)

res = 0
for v in range(1,m+1):
    #copy vertex in graph
    ng = copyVertex(graph, v, n+m+4, source, sink)
    _, f = flow(ng,sink)
    res = max(res, f)
    
print(res)
