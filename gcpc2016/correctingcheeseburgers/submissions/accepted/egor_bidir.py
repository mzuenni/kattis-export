# a bidirectional bfs
#   
#   translation of egor_bidir_hash.cpp to python
#

from collections import deque as Queue

goals= [0, 1, 12, 123, 1234, 12345, 123456, 1234567, 12345678, 123456789];

def decode(ident,  res):
    N=len(res)
    for i in range(N):
        res[N-i-1]=ident%10
        ident//=10;

def encode(orig):
    res=0
    for v in orig:
        res=res*10+v
    return res
    
    
def bit_shuffle(orig, first, second, third):
    return encode(orig[second:third]+orig[0:first]+orig[third:]+orig[first:second])
    
    

def bit_shuffle_back(orig, first, second, third):
    return encode(orig[first:second]+orig[third:]+orig[0:first]+orig[second:third])
    
    

def get_dist(start, N):
    goal=goals[N-1] 
    if goal==start:
        return 0;
    
    #initialization
    dist, q={},Queue()
     
    q.append(start)
    dist[start]=(0,0);
     
    q.append(goal);
    dist[goal]=(0,1)#1 means backwards
    
    
    while q:
        ident=q.popleft()
        info=dist[ident]
        orig=[0]*N
        decode(ident, orig)
        #brute force all possibilities
        for i in range(N+1):
            for j in range(i,N+1):
                for k in range(j,N+1):
                  next_id=bit_shuffle(orig,i,j,k) if info[1]==0 else bit_shuffle_back(orig,i,j,k)
                  next_info=dist.get(next_id)          
                  if(next_info is None):
                       dist[next_id]=(info[0]+1, info[1])
                       q.append(next_id)                
                  elif next_info[1]!=info[1]: #different start points mean a way found!
                     return next_info[0]+info[0]+1
    return -1;

#main:

N=int(input())
start=encode([int(z)-1 for z in input().split()])


print(get_dist(start, N))

