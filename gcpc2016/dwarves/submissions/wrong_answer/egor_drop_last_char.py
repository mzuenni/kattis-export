# the last char of the name is dropped during the parsing

def read_edge():
    first, sep, second=input().split()
    if len(first)>1:
        first=first[0:-1] #dropping happens here
    if len(second)>1:
        second=second[0:-1]# and here
    return (first, second) if sep==">" else (second, first)

#main:
m=int(input())

in_degs={}
graph={}

for _ in range(m):
    source, dest=read_edge()
    in_degs[dest]=in_degs.get(dest, 0)+1
    in_degs[source]=in_degs.get(source, 0)
    graph[dest]=graph.get(dest,[])
    if source not in graph:
        graph[source]=[dest]
    else:
        graph[source].append(dest)

order=[name for name,x in list(in_degs.items()) if x==0]
index=0
while index<len(order):
   cur, index=order[index], index+1  
   for next in graph[cur]:
       in_degs[next]-=1
       if in_degs[next]==0:
            order.append(next)

            
print("impossible" if len(order)!=len(in_degs) else "possible")
    
    
