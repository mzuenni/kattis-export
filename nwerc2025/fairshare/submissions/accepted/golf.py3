x=[eval(input().replace(' ','-'))for _ in[0]*int(input())]
D=sum(x)
x=[d-(D<d)*9e9for d in x]
m=max(x)
print([f'{x.index(m)+1}','impossible'][D-m>4e9])
