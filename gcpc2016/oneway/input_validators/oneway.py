#tests only that there are no multi-edges and no self-edges
#everything else handled by *.ctd

n=int(input())
m=int(input())

edges=set()

for _ in range(m):
    edge=list(map(int, input().split()))
    edge=(min(edge), max(edge))
    if edge[0]==edge[1]:
       exit(2)#selfedge!
    if edge in edges:
        exit(3)#multiedge!
    edges.add(edge)

exit(42)
   
