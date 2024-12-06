#!/usr/bin/env python3

n = int(input())
a = [int(x) for x in input().split()]
t = sum(a)
req = t//2 + 1
a.sort(reverse=True)
dp=[0]*(t+1)
dp[0] = 1
ans = 0
for i in range(n):
    add = [dp[j-a[i]] if j>=a[i] else 0 for j in range(t+1)]
    ans += sum(add[req:req+a[i]])
    dp = [dp[j]+add[j] for j in range(t+1)]
print(ans)
