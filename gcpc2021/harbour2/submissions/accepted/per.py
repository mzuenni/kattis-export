#!/usr/bin/env python3

def csum(idx):
    ans = 0
    while idx > 0:
        ans += bit[idx]
        idx -= idx & -idx
    return ans

def add(idx, v):
    idx += 1
    while idx < len(bit):
        bit[idx] += v
        idx += idx & -idx

(n, s1, s2) = map(int, input().split())
X = list(map(int, input().split())) + list(map(int, reversed(input().split())))
pos = [0]*(n+1)
bit = [0]*(n+1)
for i in range(n+1):
    pos[X[i]] = i
    add(i, 1)

at = s1
ans = 1
for i in range(1, n+1):
    real_at = csum(at)
    real_0 = csum(pos[0])
    ans += real_at-1 <= real_0 <= real_at
    add(pos[i], -1)
    at = pos[i] + (at > pos[i])

print(ans)


