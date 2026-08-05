# for every edge do bfs from end node to start node and check whether a way (contradiction) exist
# runs in O(m*(n+m)) and should tle

# max number of dwarfs:

from collections import deque as Queue



n=10000
graph=[list() for _ in range(n)]

#per bfs:
def way_exists(graph, start, end):
    if start==end: return True
    
    used, q=[False]*n,Queue()
    used[start]=True
    q.append(start)
    while q:
        cur=q.popleft()
        for next in graph[cur]:
            if next == end:
                return True
            if not used[next]:
                q.append(next)
                used[next]=True
    return False;

def read_edge():
    first, sep, second=input().split()
    return (first, second) if sep==">" else (second, first)

def contradictions_exist(graph):
    for start_node in range(n):
        for end_node in graph[start_node]:
            if way_exists(graph, end_node, start_node):
                return True
    return False

#main:
m=int(input())
 
nameMap={}
def get_id(name):
    global nameMap
    if name not in nameMap:
        nameMap[name]=len(nameMap)
    return nameMap[name]


for _ in range(m):
    source, dest=list(map(get_id, read_edge()))
    graph[source].append(dest)
        
         
print("impossible" if contradictions_exist(graph) else "possible")
    
    
