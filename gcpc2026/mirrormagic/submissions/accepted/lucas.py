from functools import *
add = lambda p,q: (p[0]+q[0], p[1]+q[1])
mul = lambda a,v: (a*v[0], a*v[1])
dot = lambda p,q: p[0]*q[0] + p[1]*q[1]
def imp(): print("impossible"); exit(0)

n = int(input())
pts = [(*map(int, input().split()),) for i in range(2*n)]
c = mul(.5/n, reduce(add, pts))
d = add(c, mul(-1/n, reduce(add, pts[:n])))
l = (d[0]**2+d[1]**2)**.5
if l < 1e-12: imp()
d = mul(1/l, d)
cd = dot(c, d)
s = {*pts[n:]}
for p in pts[:n]:
	r = dot(p, d)
	q = add(p, mul(2*(cd-r), d))
	if r > cd: imp()
	q2 = (round(q[0]), round(q[1]))
	if max(map(abs, add(mul(-1, q), q2))) > 1e-6: imp()
	if not q2 in s: imp()

print("possible\n")
