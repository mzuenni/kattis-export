import sys
import random

n = int(sys.argv[1])
random.seed(int(sys.argv[2]))
assert(n % 6 == 2)
print(1)
print(n)
X = 10**9
print(0, 0, X, 0)
print(0, 4, X, 4)

offset = 0

bad = random.randint(0, n//3 - 1)
for i in range(n // 3):
    print(1 + offset, 0, 1 + offset, 2)
    if i == bad:
        print(1 + offset, 2, 3 + offset, 2)
    else:
        print(1 + offset, 2, 2 + offset, 2)
    print(2 + offset, 2, 2 + offset, 4)

    offset += 10
