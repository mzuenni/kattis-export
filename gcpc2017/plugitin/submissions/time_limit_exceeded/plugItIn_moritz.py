'''
Created on 02.05.2017

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

# compute bipartite matching on initial graph    
augmented_graph = deepcopy(graph)
augmented_graph, f = flow(augmented_graph, sink)
res = f

# Add extra copies of interesting sockets, continue computing matching
for i in range(1,m+1):
    # if socket i has only 1 neighbor, nothing will change by adding copies.
    # if socket i is not connected to the source it was not matched. Hence nothing will change by adding copies.
    if len(graph[i]) > 1 and source in augmented_graph[i]:
        # copy graph with 2 additional copies of socket i
        augmented_graph_copy = deepcopy(augmented_graph)
        #source to copy
        augmented_graph_copy[0].add(n+m+4)
        augmented_graph_copy[0].add(n+m+5)
        
        for x in graph[i]:
            augmented_graph_copy[n+m+4].add(x)
            augmented_graph_copy[n+m+5].add(x)
        
        # resume computing the matching from previous result with 2 extra copies of socket i
        res = max(res, flow(augmented_graph_copy, sink, f)[1])

print(res)
