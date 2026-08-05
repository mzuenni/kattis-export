# there is a liar iff a dag sorting is not possible
# uses names as ids, no integral aliases

#can lead to O(n^2) behavior

def read_edge():
    first, sep, second=input().split()
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
    graph[source]=graph.get(source,[])+[dest]#PROBLEM: too cool, leads to n^2

order=[name for name,x in list(in_degs.items()) if x==0]
index=0
while index<len(order):
   cur, index=order[index], index+1  
   for next in graph[cur]:
       in_degs[next]-=1
       if in_degs[next]==0:
            order.append(next)

            
print("impossible" if len(order)!=len(in_degs) else "possible")
    
    
