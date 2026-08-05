#checks  1. |p|>=0.1 #exit=2
#        2. 0.1<=|t|<=0.95 #exit=3
#        3. 10<=angle<=90 #exit=4
#        4. dist to intersection with plane == d or |dist-d|>0.1ly # exit=5
#        5. dist to plane at the time of transmission 0.0 or >0.1ly # exit=6
#        6. stars do not collide (not done because too slow)

import math
def dot(a,b):
    return sum([x1*x2 for x1,x2 in zip(a,b)])
    
def length(a):
    return math.sqrt(dot(a,a)) 
    
def minus(a,b):
    return [x-y for x,y in zip(a,b)]
    
def normalize(a):
    n=length(a)
    return [x/n for x in a]
    
def cross(a,b):
    return [a[1]*b[2]-a[2]*b[1], b[0]*a[2]-a[0]*b[2], a[0]*b[1]-a[1]*b[0]]

def evaluate(s,t,tau):
    return [x1+tau*x2 for x1,x2 in zip(s,t)]

EPS=1e-6
COS_80=0.17364817766693041

def do_collide(s1, t1, s2, t2):
    diff_s=minus(s1, s2)
    diff_t=minus(t1, t2)
    le_s=length(diff_s)
    le_t=length(diff_t)
    if le_t<EPS:
        return True if le_s<EPS else False
    tau=le_s/le_t
    def equal(ds, dt, tau):
       return max([abs(a-tau*b) for a,b in zip(ds, dt)])<EPS
    return equal(diff_s, diff_t, tau) or equal(diff_s, diff_t, -tau)

    
temp1, temp2=input().split()
n, d=int(temp1), float(temp2)

p1=list(map(float, input().split()))
p2=list(map(float, input().split()))

plane_normal=normalize(cross(p1, p2))



if length(p1)<0.1 or length(p2)<0.1:
    print("p-vectors too short!")
    exit(2)

trajectories=[]
for _ in range(n):
     s, t=[list(map(float, input().split())) for _ in range(2)]
     lenT=length(t)
     if lenT<0.1 or lenT>0.95:
        print("invalid t-length for trajectory", _)
        exit(3)      
     trajectories.append((s,t))

for i in range(n):
    #angle:
    s,t=trajectories[i]
    if abs(dot(plane_normal, t))<COS_80*length(t):
        print("the angle of the trajectory", i, "is too small")
        exit(4)
        
    #distance to the intersection point with the plane
    tau=-dot(plane_normal, s)/dot(plane_normal, t) 
    dist_diff=abs(length(evaluate(s,t,tau))-d)  
    if(dist_diff>EPS and dist_diff<0.1):
       print("invalid distance to intersection with the plane for trajectory ", i)
       exit(5)
       
    #time over plane:
    pos_over_plane=abs(dot(plane_normal, evaluate(s,t, -d)))
    if(pos_over_plane>EPS and pos_over_plane<0.1):
       print("invalid distance to the plane at the time of the transmission for trajectory ", i)
       print("s=", s, "t=", t, "plane_normal=", plane_normal)
       print("position at time of transmission=", evaluate(s,t, -d))
       print("dist to plane=", pos_over_plane)
       exit(6)


    #Because of O(N^2) too slow     
    #collision:
    #for j in xrange(i+1, n):
    #    if do_collide(s,t, trajectories[j][0], trajectories[j][1]):
    #        print "trajectories", i, "and", j, "do collide!"
    #        exit(7)#the trajectories shall not intersect!
        

exit(42)
