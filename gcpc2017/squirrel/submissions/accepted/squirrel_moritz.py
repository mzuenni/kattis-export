'''
Created on 04.05.2017

@author: Moritz Fuchs
'''
from collections import defaultdict
from math import ceil

def getVertexWithMaxDist(start):
    global adj
    q = [(start,1)]
    seen = set()
    seen.add(start)
    m = -1
    max_dist = -1
    while q:
        current, dist = q.pop(0)
        if dist > max_dist:
            m = current
            max_dist = dist
        
        for x in adj[current]:
            if x not in seen:
                q.append((x, dist+1))
                seen.add(x)
    return (m, max_dist)

def diameter():
    return getVertexWithMaxDist(getVertexWithMaxDist(squirrel)[0])[1]

def dfs(start, parent, c_depth, depth):
    global adj
    depth[start] = c_depth
    res = c_depth
    for x in adj[start]:
        if x != parent:
            res = max(res, dfs(x, start, c_depth+1, depth))
    return res

def subtreeDepth(raven):
    for x in adj[raven]:
        depth = [-1]*n
        res = dfs(x,raven,1,depth)
        if depth[squirrel] != -1:
            return res
 
    return -1  

n = int(raw_input())
squirrel = int(raw_input())-1
raven1 = int(raw_input())-1
raven2 = int(raw_input())-1
adj = defaultdict(lambda:list())
for _ in range(n-1):
    start, end = map(int, raw_input().split())
    start -= 1
    end -= 1
    adj[start].append(end)
    adj[end].append(start)

#print(diameter())
#print(subtreeDepth(raven1))
#print(subtreeDepth(raven2))

dist = min(ceil((1+float(diameter()))/2), subtreeDepth(raven1), subtreeDepth(raven2)) 

print(int(dist))
    
