#!/usr/bin/env python3

n = int(input())
print("?", n, 1)
fn1 = int(input())
if fn1 == n:
    print("!", n, 1)
else:
    print("?", n - fn1, 1)
    x = int(input())
    print("!", fn1, x)
