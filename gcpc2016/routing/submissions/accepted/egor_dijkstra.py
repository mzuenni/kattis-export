# using as states (current_server, predecessor_server)
#       as edges (current_server, predecessor_server)->(next_server, current_server) with weight time of current_server
#       
# und dikstra on the graph starting in (0, XXX) and ending in (n-1, XXX), adjusting the costs with the time of the of the last server


n=int(input())

#first index - current node, second index predecessor
graph=[[list() for _ in range(n)] for __ in range(n)]
times=[]

for i in range(n):
    m, t=list(map(int, input().split()))
    times.append(t)
    for _ in range(m):
        line=list(map(int, input().split()))
        if line[0]:
            x, forbidden = line[1]-1, set(line[2:])
        else:
            x, forbidden = line[1]-1, set()
        for parent in range(n):
            if parent+1 not in forbidden:
                graph[i][parent].append([x,i,t])#goal, predecessor, time/cost

from heapq import *

MAX_VAL=float("inf")

q=[]
dists=[[MAX_VAL]*n for _ in range(n)]
for start in range(0,n):
    dists[0][start]=0
    heappush(q, (0, 0, start))
    
while q:
    d, cur, pred = heappop(q)
    if d!=dists[cur][pred]:
        continue
    for edge in graph[cur][pred]:
        next, next_pred=edge[0], edge[1]
        nextDist=d+edge[2]
        if nextDist<dists[next][next_pred]:
            dists[next][next_pred]=nextDist
            heappush(q, (nextDist, next, next_pred))
                
                
best=min(dists[-1])
	
print(best+times[-1] if best!=MAX_VAL else "impossible")
        
    
