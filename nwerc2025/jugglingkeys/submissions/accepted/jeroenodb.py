#!/usr/bin/env python3
n,k,q = map(int,input().split())
ans,u = [0]*q,0
e = sorted(v for y in range(q) for v in ((int(x), (i+1)%3-1,y) for i,x in enumerate(input().split())) if v[1])
for x,t,w in e: ans[w], n = int(n==0 and t==-1), n-t
[exit(print("IMPOSSIBLE")) for x,t,w in e if (u:=u+ans[w]*t)>k], print(*ans,sep="")