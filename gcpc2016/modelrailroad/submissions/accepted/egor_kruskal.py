#find the MST, check whether MST is really a tree and not a forest, check the weight of the MST not greater than available material
#using kruskal & find-union by rank with compression

class FindUnion:
    def __init__(self, n):
        self.parent=list(range(n))
        self.rank=[0]*n
    
    def find(self,i):
        while(i!=self.parent[i]):
            j=self.parent[i]
            self.parent[i]=self.parent[j]
            i=j
        return i
    
    def union(self,i,j):
        pi, pj=self.find(i), self.find(j)
        if pi==pj:
            return False
        if self.rank[pi]>self.rank[pj]:
            self.parent[pj]=pi
        else:
            self.parent[pi]=pj
            if self.rank[pi]==self.rank[pj]:
                self.rank[pi]+=1
        return True

#main
n, m, l = list(map(int, input().split()))
fu=FindUnion(n)

edges=[]
available=0
for i in range(m):
    s, t, w = list(map(int, input().split()))
    edges.append([w,s,t])
    if i<l:
        available+=w
        
#kruskal
cnt, weight = 0,0
edges.sort()
for edge in edges:
    if fu.union(edge[1]-1, edge[2]-1):
        weight+=edge[0]
        cnt+=1

if cnt==n-1 and weight<=available:
    print("possible")
else:
    print("impossible")
