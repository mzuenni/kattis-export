#!/usr/bin/env python3
h,w,k,i,t = map(int, input().split())

data = [['A'] * w for _ in range(h)]

for r in range(h):
    for c in range(w):
        if r == 0 and c == 0:
            data[r][c] = 'K'
            k -= 1
            continue
        if r == 0 and c == 1:
            data[r][c] = 'I'
            i -= 1
            continue
        if r == 0 and c == 2:
            data[r][c] = 'T'
            t -= 1
            continue
        if k > 0:
            data[r][c] = 'K'
            k -= 1
        elif t > 0:
            data[r][c] = 'T'
            t -= 1
        elif i > 0:
            data[r][c] = 'I'
            i -= 1

for r in range(h):
    print(''.join(data[r]))
