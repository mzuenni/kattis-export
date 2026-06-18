n,k=map(int,input().split())
print(("bc"*n)[:(n-k)//2] + "a" * k + ("ef"*n)[:(n-k+1)//2])
