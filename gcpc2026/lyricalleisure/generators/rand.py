import sys
import random


# Init seed with first argument
random.seed(int(sys.argv[1]))
if len(sys.argv) >= 3:
    L = int(sys.argv[2])
else:
    L = 1

if len(sys.argv) >= 4:
    R = int(sys.argv[3])
else:
    R = 100000

n = random.randint(L, R)

if len(sys.argv) >= 5:
    Lk = int(sys.argv[4])
else:
    Lk = L

if len(sys.argv) >= 6:
    Rk = min(n, int(sys.argv[5]))
else:
    Rk = n

k = random.randint(Lk, Rk)

print(n, k)
