#!/usr/bin/python3
import sys

n = int(sys.argv[1])
X = int((-1 + (1 + 4*n) ** .5) / 2) + 1
assert(X + X*X >= n)

print(1)
print(n)
left = n - X
for i in range(X):
    x = 1 + 3*i
    print(x, 0, x, 3*(X+1))
    for j in range(X):
        if left:
            left -= 1
            print(x-1, 3*j+1, x+1, 3*j+1) 
