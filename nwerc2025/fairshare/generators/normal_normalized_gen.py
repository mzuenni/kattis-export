import random
import sys

n = int(sys.argv[1])
mu = int(sys.argv[2])
sigma = float(sys.argv[3])
tau = float(sys.argv[4])
sigma_prime = float(sys.argv[5])
seed = int(sys.argv[6])

random.seed(seed)
print(n)

A = []
B = []
sumD = 0
maxD = -2000000000
maxI = -1
for i in range(n):
	c = random.gauss(mu, sigma)
	eps = random.gauss(tau/2, sigma_prime/2)
	a = min(max(round(c - eps), 1), 1000)
	b = min(max(round(c + eps), 1), 1000)
	d = b-a;
	sumD += d
	if d > maxD:
		maxD = d
		maxI = i
	A.append(a)
	B.append(b)

for i in range(n):
	if i == maxI: continue
	rem = n-i
	if i < maxI: rem -= 1
	change = (sumD-maxD+rem-1)//rem
	B[i] -= change//2
	A[i] += (change+1)//2
	sumD -= change
	d1 = max(0, 1-A[i], 1-B[i])
	d2 = min(0, 1000-A[i], 1000-B[i])
	A[i] += d1+d2
	B[i] += d1+d2
	
for i in range(n):
	print(A[i], B[i])

