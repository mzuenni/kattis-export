#!/usr/bin/env python3

n, k = map(int, input().split())
p = [-1] + [int(x)-1 for x in input().split()]

res = []
h = [1] * n
for i in range(n)[::-1]:
  if h[i] == k or i == 0:
    h[i] = 0
    res.append(i+1)
  h[p[i]] = max(h[p[i]], 1+h[i])

print(len(res))
print(*res)
