#DP in O(m*c^2)
c,m=list(map(int, input().split()))

best=[0]*(c+1)

for _ in range(m):
    ps=list(map(int, input().split()))
    for i in reversed(range(c)):
       for k in range(c-i-1):#should be c-i-1
           best[i+k+1]=max(best[i+k+1], best[i]+ps[k])
           
print(max(best))

