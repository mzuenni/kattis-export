import random
import sys

# everyone pays what they spent except for 8 ppl paying 1 more and 1 paying 9 less

seed = int(sys.argv[1])
n = int(sys.argv[2])
x = int(sys.argv[3])

random.seed(seed)

good_ones = random.sample(range(n), 9)
payer = good_ones.pop()

print(n)
for i in range(n):
	a = b = random.randint(1, x)
	if i in good_ones:
		a+=1
	if i == payer:
		b+=len(good_ones)+1
	print(a, b)
