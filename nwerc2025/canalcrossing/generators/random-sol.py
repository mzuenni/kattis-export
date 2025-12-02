import sys, random

random.seed(int(sys.argv[1]))
n = int(sys.argv[2])
m = int(sys.argv[3])
prob = float(sys.argv[4])
k = n//5
root = random.randint(0,n-k-1)
at = root
es = set() # (u,v) 
while len(es)<m*3//5 or at!=root:
    nxt = random.randint(0,n-k-1)
    if len(es)>m*3//5:
        if random.randint(0,1):
            nxt = root
    if nxt!=at and (at,nxt) not in es and (nxt,at) not in es:
        es.add((at,nxt))
        at=nxt

par = [*range(n)]
def find(x):
    if x==par[x]: return x
    p = find(par[x])
    par[x]=p
    return p
comps = n
def unite(u,v):
    global comps
    u = find(u)
    v= find(v)
    if u==v: return False
    par[u]=v
    comps-=1
    return True
tree = []
for u,v in es:
    if random.random()<=prob:
        if unite(u,v):
            tree.append((u,v))

es = es - set(tree)

while comps!=1:
    u = random.randint(0,n-1)
    v = random.randint(0,n-1)
    if (u,v) not in es and (v,u) not in es and unite(u,v):
        tree.append((u,v))

perm = [*range(n)]
random.shuffle(perm)
es = sorted(es)
random.shuffle(es)
random.shuffle(tree)

print(n)

for u,v in tree:
    if random.randint(0,1): u,v=v,u
    print(perm[u]+1,perm[v]+1,random.randint(1,10**6))

print(len(es))
for u,v in es:
    if random.randint(0,1): u,v=v,u
    print(perm[u]+1,perm[v]+1)