# there is a liar iff a dag sorting is not possible
# max number of dwarfs:
n=10000

def read_edge():
    first, sep, second=input().split()
    return (first, second) if sep==">" else (second, first)

#main:
m=int(input())

in_degs=[0]*n
graph=[list() for _ in range(n)]

   
nameMap={}
def get_id(name):
    global nameMap
    if name not in nameMap:
        nameMap[name]=len(nameMap)
    return nameMap[name]


for _ in range(m):
    source, dest=list(map(get_id, read_edge()))
    in_degs[dest]+=1
    graph[source].append(dest)


order=[i for i,x in enumerate(in_degs) if x==0]
index=0
while index<len(order):
   cur, index=order[index], index+1  
   for next in graph[cur]:
       in_degs[next]-=1
       if in_degs[next]==0:
            order.append(next)
            
print("impossible" if len(order)!=n else "possible")
    
    
