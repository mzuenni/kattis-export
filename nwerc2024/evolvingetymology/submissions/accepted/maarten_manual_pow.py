#!/usr/bin/env python3

(n, k), s = map(int, input().split()), input()
offset, base = 1, 2
while k > 0:
    if k & 1:
        offset = (offset * base) % n
    k >>= 1
    base = (base * base) % n
print("".join(s[i * offset % n] for i in range(n)))
