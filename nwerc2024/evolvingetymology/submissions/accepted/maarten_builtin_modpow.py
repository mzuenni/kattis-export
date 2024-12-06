#!/usr/bin/env python3

(n, k), s = map(int, input().split()), input()
print("".join(s[i * pow(2, k, n) % n] for i in range(n)))
