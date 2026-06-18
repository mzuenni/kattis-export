from itertools import *
n, m = map(int, input().split())
e = [(*map(int, input().split()),) for _ in range(m)]
p, c, s, ans = [*range(n+1)], [0]*(n+1), [(1,0)]*(n+1), 0
def qry(x):
	r = 0
	while x != p[x]: c[x] ^= c[p[x]]; p[x] = p[p[x]]; r ^= c[x]; x = p[x]
	return x, r
def join(u,v):
	u, uc = qry(u); v, vc = qry(v); uc ^= vc^1
	if u == v and uc: exit(print("impossible"))
	if u != v: s[v] = [s[v][i]+s[u][uc^i] for i in [0,1]]
	p[u], c[u] = v, uc
	return v
l = lambda x: -x[2]
for _, g in groupby(sorted(e, key=l), l):
	vis = set(starmap(join, [(qry(u)[0], qry(v)[0]) for u,v,_ in g]))
	for u in vis:
		if u == p[u]:
			ans += min(s[u])
			s[u] = sum(s[u]),0
print(f"possible\n{ans}")