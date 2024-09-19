#!/usr/bin/env python3
import collections

h,w = (int(x) for x in input().split())

cnt = collections.Counter()
for i in range(0,h):
    row = input()
    lsf = -1
    last = -1
    for j in range(0,w):
        if (cnt[j]):
            if (last != -1):
                cnt[last] += 1
                last = -1
            lsf = j
        if (row[j] == '_'): continue
        if (last == -1 and lsf != -1): cnt[lsf] -= 1
        last = j
    if (last != -1):
        cnt[last] += 1

print(sum(cnt.values()))

