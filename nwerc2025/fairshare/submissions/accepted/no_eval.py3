x=[]
for _ in[0]*int(input()):
 a,b=map(int,input().split())
 x+=[a-b]
D=sum(x)
x=[d-(D<d)*9e9for d in x]
m=max(x)
print([f'{x.index(m)+1}','impossible'][D-m>1e9])
