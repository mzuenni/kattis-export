import sys
import random

n = int(sys.argv[1])
k = int(sys.argv[2])

p = []
for i in range(2, n//2):
    p.append(i-1)
for i in range(n//2, n+1):
    p.append(n//2-1)

print(n, k)
print(*p)

