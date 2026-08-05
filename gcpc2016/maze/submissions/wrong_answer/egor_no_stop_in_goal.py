#just simulate by storing the probability of being in every room

#does not accumulates the probability in the room n

n,m=list(map(int, input().split()))

graph=[{} for _ in range(n)]
for _ in range(m):
    s,t,ch=input().split()
    s,t,ch=int(s)-1, int(t)-1, ch[0]
    
    def append(s,t,ch):
        global graph 
        rooms=graph[s].get(ch,[])
        rooms.append(t)
        graph[s][ch]=rooms
    append(s,t,ch)
    append(t,s,ch)#the door works in both directions
        
        
#simulate:    
cur_prob=[1.0]+[0.0]*(n-1)
for ch in input():
    next_prob=[0.0]*n
    for i in range(n):#Nth ROOM SHOULD BE HANDLED SEPARATEDLY
        rooms=graph[i].get(ch, [])
        if rooms:
            for next in rooms:
                next_prob[next]+=cur_prob[i]/len(rooms)
        else:
            next_prob[i]+=cur_prob[i]
    cur_prob=next_prob

print(cur_prob[-1]*100.0)
 
