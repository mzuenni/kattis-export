import sys
import random

random.seed(int(sys.argv[1]))
n = int(sys.argv[2])
k = int(sys.argv[3])

p = []
remaining = [1]
tail = 1
for i in range(2, n+1):
    if random.choice([True, False]) and len(remaining) > 0:
        j = random.randrange(len(remaining))
        p.append(remaining.pop(j))
    else:
        p.append(tail)
        tail = i
        remaining.append(i)

print(n, k)
print(*p)
