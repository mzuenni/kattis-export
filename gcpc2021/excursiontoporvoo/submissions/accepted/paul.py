#!/usr/bin/env python3
n, m = map(int, input().split())
events = []
for _ in range(m):
    i, d, c = map(int, input().split())
    events.append((c,d,i-1))
q = int(input())
for j in range(q):
    w = int(input())
    events.append((w,-1,j))

best = [10**10] * (n-1)
total = sum(best)
res = [''] * q
for w, d, i in sorted(events)[::-1]:
    if d == -1:
        res[i] = str(total) if total < 10**10 else 'impossible'
    else:
        diff = max(0,best[i]-d)
        best[i] -= diff
        total -= diff

print('\n'.join(res))
