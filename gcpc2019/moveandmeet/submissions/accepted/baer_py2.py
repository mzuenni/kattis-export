def sgn(x):
	return 0 if x==0 else x // abs(x)
x1,y1,d1=map(int, raw_input().split(" "))
x2,y2,d2=map(int, raw_input().split(" "))
my=min(d2,abs(y2-y1))
d2-=my
y2+=my*sgn(y1-y2)
mx=min(d2,abs(x2-x1))
d2-=mx
x2+=mx*sgn(x1-x2)
dist = abs(x1-x2)+abs(y1-y2)
if d1 < dist or (d1-dist) % 2 != d2 % 2:
	print "impossible"
else:
	print x2 + (d1-dist) % 2, y2
