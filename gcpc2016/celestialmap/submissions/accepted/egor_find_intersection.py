# for every star finds the intersection with the plane
# checks whether the traveling time of the start/signal and distance are ok
# no corner cases, because of guaranties in the problem statements
import math
EPS=1e-6
def dot(a,b):
    return sum([x1*x2 for x1,x2 in zip(a,b)])

temp1, temp2=input().split()
n, d=int(temp1), float(temp2)

p1=list(map(float, input().split()))
p2=list(map(float, input().split()))
normal=[p1[1]*p2[2]-p1[2]*p2[1], p2[0]*p1[2]-p1[0]*p2[2], p1[0]*p2[1]-p1[1]*p2[0]]

cnt=0
for _ in range(n):
     s, t=[list(map(float, input().split())) for _ in range(2)]
     #calc time of intersection:
     tau=-dot(normal, s)/dot(normal, t)
     pos=[x1+tau*x2 for x1,x2 in zip(s,t)]
     dist=math.sqrt(dot(pos, pos))
     if abs(dist-d)<EPS and abs(dist+tau)<EPS:
        cnt+=1

print(cnt)

