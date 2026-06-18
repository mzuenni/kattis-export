#!/usr/bin/env python3

n, k = map(int, input().split())
print(('a' * k + 'bcd' * n)[:n])
