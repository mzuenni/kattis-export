#!/usr/bin/env python3
import sys

d = dict()
for k in range(5):
    s = ''
    for i in range(1,27):
        if i & (1<<k):
            s += chr(96+i)
    print(s)
    sys.stdout.flush()
    js = map(int, input().split()[1:])
    for j in js:
        if j not in d:
            d[j] = 96
        d[j] |= 1<<k

print(''.join(chr(x[1]) for x in sorted(d.items())))
