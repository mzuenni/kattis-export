# this is a translation of per.cc to python

N,K=list(map(int, input().split()))
gs=list(map(int, input().split()))
MAX=gs[0]
gs=gs[1:]

minv=[K+1]*MAX
minv[K%MAX]=0

for w in gs:
    t=1;
    while(t<MAX):
        for x in range(MAX):
            minv[x] = min(minv[x], minv[(x+t*w) % MAX] + t*w)
        t*=2

print("possible" if minv[0]<=K else "impossible")  


