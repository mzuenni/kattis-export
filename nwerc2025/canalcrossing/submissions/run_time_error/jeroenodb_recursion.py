#!/usr/bin/env python3
# forgot to do recursion limit
n = int(input())
adj = [[] for i in range(n)]
for i in range(n-1):
    u,v,w=map(int,input().split())
    u-=1
    v-=1
    adj[u].append((v,w))
    adj[v].append((u,w))
deg = [False]*n
m = int(input())
for i in range(m):
    for u in map(int,input().split()):
        deg[u-1] = not deg[u-1]
ans=0
def dfs(at,frm) -> bool:
    global ans
    cur=deg[at]%2==1
    for to,w in adj[at]:
        if to!=frm:
            if dfs(to,at):
                ans+=w
                cur = not cur
    return cur
dfs(0,-1)
print(ans)