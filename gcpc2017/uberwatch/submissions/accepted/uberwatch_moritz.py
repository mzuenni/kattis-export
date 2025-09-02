'''
Created on 18.05.2017

@author: Moritz Fuchs
'''

n,m = map(int,raw_input().split())
x = list(map(int,raw_input().split()))

dp = [0]*n
for i in range(m,n):
    dp[i] = max(dp[i-1], dp[i-m] + x[i])
print(dp[n-1])

