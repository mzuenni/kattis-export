#!/usr/bin/env python3
import random

random.seed(987)

a = map(int, input().split())

dp = [1]
for k, s in zip(a, [4,6,8,12,20]):
  for _ in range(k):
    ndp = [0] * (len(dp)+s+1)
    for i, x in enumerate(dp):
      for j in range(1, s+1):
        ndp[i+j] += x
    dp = ndp

res = [i for i, x in enumerate(dp) if x > 0]
random.shuffle(res)
res.sort(key=lambda i: -dp[i])
print(*res)
