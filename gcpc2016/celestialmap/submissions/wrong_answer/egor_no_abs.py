# for every star it finds the time  the signal was send by solving |s+pt\tau|=|\tau|,
# calculates position for the time \tau and checks whether it is on the plane (n\cdot pos \approx 0.0)
# a little bit tricky for 1-p << 1
import math

EPS=1e-6

def dot(a,b):
    return sum([x1*x2 for x1,x2 in zip(a,b)])

temp1, temp2=input().split()
n, d=int(temp1), float(temp2)

p1=list(map(float, input().split()))
p2=list(map(float, input().split()))
normal=[p1[1]*p2[2]-p1[2]*p2[1], p2[0]*p1[2]-p1[0]*p2[2], p1[0]*p2[1]-p1[1]*p2[0]]


#guaranties of 0.1ly and 10 grad should be enough for 1e-2
nn=1e-2*math.sqrt(dot(normal, normal))

cnt=0
for _ in range(n):
     s, t=[list(map(float, input().split())) for _ in range(2)]
     #calc time:
     st=dot(s,t)
     ss=dot(s,s)
     pp=1-dot(t,t)#t^2<9.5, nothing to worry about!
     a=st/pp
     tau=a-math.sqrt(a*a+ss/pp)
     #check position:
     pos=[x1+tau*x2 for x1,x2 in zip(s,t)]
     if abs(dot(pos, normal))<nn and tau+d<EPS:# <------ here we go, if tau<d
        cnt+=1

print(cnt)

