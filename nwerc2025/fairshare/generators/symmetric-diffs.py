import sys, random

random.seed(int(sys.argv[1]))
n = int(sys.argv[2])

a = []
b = []

M = random.randint(1, 499)

for i in range((n+1)//2):
	x = random.randint(0, M-1)
	if i+1 == (n+1)//2: x = M
	offset = random.randint(500, 1000)
	a.append(offset - x)
	b.append(offset)
	a.append(offset)
	b.append(offset - x)

a.pop()
b.pop()

if n % 2 == 0:
	a.append(1)
	b.append(1)

perm = list(range(0, n))
for i in range(1, n):
	j = random.randint(0, i)
	a[i], a[j] = a[j], a[i]
	b[i], b[j] = b[j], b[i]

print(n)
for x, y in zip(a, b):
	print(x, y)
