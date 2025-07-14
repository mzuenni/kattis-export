n,t=map(int,input().split())
a=[*map(int,input().split())]+[i:=0]
while-t<0<=i<n:
 if a[i]:
  a[p:=i]+=1
  t-=1
  while-a[p]<-1<p<n:
   x,a[p]=min(a[p],n-p),0
   for x in[0]*x:a[p:=p+1]+=1
 a[i]=t%2
 a[(i:=i+2)-1]+=(t:=t//2)
print(*a[:-1])
