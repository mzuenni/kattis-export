#emulates wrong solution, which assumes we can get at least 1 money unit per CPU
c,m=list(map(int, input().split()))

best=[0]*(c+1)

for _ in range(m):
    ps=list(map(int, input().split()))
    for i in reversed(range(c)):
       for k in range(c-i):
           best[i+k+1]=max(best[i+k+1], best[i]+ps[k])
           
print(max(c, max(best))) # here we go

