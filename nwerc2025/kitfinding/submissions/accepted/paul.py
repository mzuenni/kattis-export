#!/usr/bin/env python3

h, w, k, i, t = map(int, input().split())
s = 'KI' + 'T' * t + 'K' * (k-1) + 'I' * (i-1)
print('\n'.join(s[j:j+w] for j in range(0, h*w, w)))
