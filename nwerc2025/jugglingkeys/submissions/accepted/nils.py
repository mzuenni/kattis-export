#!/usr/bin/env python3

n,k,q = map(int,input().split())

ans = ['0'] * q

events = []

for i in range(q):
    person, t1, t2 = map(int,input().split())
    events.append((t1, i, 1))
    events.append((t2, i, -1))
events.sort()

gone = 0

for i in range(len(events)):
    t, i, d = events[i]
    if gone == n and d == -1:
        ans[i] = '1'
    gone += d

keys = k

for i in range(len(events)):
    t, i, d = events[i]
    d *= int(ans[i])
    keys -= d
    if keys < 0:
        print("impossible")
        exit()
print("".join(ans))

