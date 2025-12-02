import math
n = int(input())

mx = 1
def res(x):
    return n/math.gcd(n,x) * math.sin(math.pi * x / n)
for x in range(1,n//2+1):
    if res(x) >= res(mx):
        mx = x
print(mx)
