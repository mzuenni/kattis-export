#!/usr/bin/env python3

n, k = int(input()), 3

vals = input()
X = vals.count("r")
Y = vals.count("g")
Z = vals.count("b")
[X, Y, Z] = sorted([X, Y, Z], reverse=True)

# Always a>=b>=c
parts = {}

if k == 3:
    for a in range(0, n+1):
        for b in range(0, a + 1):
            c = n - a - b
            if c > b:
                continue
            if c < 0:
                continue
            parts[(a, b, c)] = 0
    for _ in range(1000):
        for (a, b, c) in list(parts.keys()):
            if a == n:
                continue
            if c > 0:
                if a > b:
                    parts[(a, b, c)] = 1+ (parts[(a,b,c)] + parts[(a+1, b, c-1)] + parts[(a, b+1, c-1)])/3
                else:
                    parts[(a, b, c)] = 1+ (parts[(a,b,c)] + 2*parts[(a+1, b, c-1)])/3
            else:
                if b > 1:
                    parts[(a, b, c)] = 1+ (parts[(a,b,c)] + parts[(a+1, b-1, 0)] + parts[(a, b-1, 1)])/3
                else:
                    parts[(a, b, c)] = 1+ (parts[(a+1,0,0)] + 2*parts[(a, 1, 0)])/3
    print(parts[(X, Y, Z)])
else:
    assert k==2
    for a in range(0, n+1):
        b = n - a
        if b > a:
            continue
        if b < 0:
            continue
        parts[(a, b)] = 0
    for _ in range(1000):
        for (a, b) in list(parts.keys()):
            if a == n:
                continue
            parts[(a, b)] = 1+ (parts[(a,b)] + parts[(a+1, b-1)])/2
    print(parts[(X, Y)])
