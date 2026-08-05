# pretty stupid, looks only if there is an node with incoming degree 0


def read_edge():
    first, sep, second=input().partition(" > ")
    if sep:
        return (first, second)
    first, sep, second=first.partition(" < ")
    return (second, first)


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

            
print("impossible" if not order else "possible")
    
    
