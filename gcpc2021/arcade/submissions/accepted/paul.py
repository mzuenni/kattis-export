#!/usr/bin/env python3

def solve(n):
    if n <= 3: return 1
    for a in range(1,64):
        for b in range(1,64):
            if 2**a + 2**b + 1 == n:
                return str(2**a + 1)
    return 'impossible'

print(solve(int(input())))
