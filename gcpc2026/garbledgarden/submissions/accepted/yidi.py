import sys
sys.setrecursionlimit(10000)

def add(a, x):
    for i in range(len(a)):
        a[i] += x

cycle = []
def euler(u):
    while adj[u]:
        v, x = adj[u].pop()
        euler(v)
        cycle.append(x)

n = int(input())
a = [*map(int, input().split())]
add(a, -1)

a2 = sorted(a)
adj = [[] for i in range(n)]
for it in range(2):
    rev = [0] * n
    for i in range(n):
        if a[i] != a2[i]:
            adj[a[i]].append((a2[i], i))
            rev[a[i]] = i
    
    comps = []
    cycle = []
    for i in range(n):
        if adj[i]:
            comps.append(rev[i])
            euler(i)
    cycle.reverse()

    if not comps:
        print(0)
        exit(0)

    if len(comps) == 1:
        if it == 0:
            print(1)
        print(len(cycle))
        add(cycle, 1)
        print(*cycle)
        exit(0)

    a3 = a[:]
    for i in range(len(comps)):
        a[comps[i]] = a3[comps[(i+1)%len(comps)]]
    
    print(2)
    print(len(comps))
    add(comps,1)
    print(*comps)
