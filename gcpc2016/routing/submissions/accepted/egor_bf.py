# using as states (current_server, predecessor_server)
#       as edges (current_server, predecessor_server)->(next_server, current_server) with weight time of current_server
#       
# and bellman-ford on the graph starting in (0, XXX) and ending in (n-1, XXX), adjusting the costs with the time of the last server

MAX_VAL=10**9

#input:
n=int(input())
edges=[]
for i in range(n):
    m, time=list(map(int, input().split()))
    for _ in range(m):
        line=list(map(int, input().split()))
        if line[0]:
            x, forbidden = line[1]-1, set(line[2:])
        else:
            x, forbidden = line[1]-1, set()
        for parent in range(n):
            if parent+1 not in forbidden:
                edges.append((i, parent, x, time))

#bellman-ford:
dists=[[MAX_VAL]*n for _ in range(n)] 
dists[0]=[time]*n #time from the last server
   
changed=True
while(changed):
    changed=False
    for edge in edges:
        next_dist=dists[edge[0]][edge[1]]+edge[3] #don't mind if not set-> than no improvement anyway
        if next_dist<dists[edge[2]][edge[0]]:
            dists[edge[2]][edge[0]]=next_dist
            changed=True

#output:
best=min(dists[n-1])
print(best if best!=MAX_VAL else "impossible")
        
    
