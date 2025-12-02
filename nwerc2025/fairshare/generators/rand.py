import random
import sys

seed = int(sys.argv[1])
n = int(sys.argv[2])
x = int(sys.argv[3])
y = int(sys.argv[4])

random.seed(seed)
print(n)
for _ in range(n):
	print(random.randint(1, x), random.randint(1, y))
