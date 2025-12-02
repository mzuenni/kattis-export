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
for i in range(n):
	c = random.gauss(mu, sigma)
	eps = random.gauss(tau/2, sigma_prime/2)
	a = min(max(round(c - eps), 1), 1000)
	b = min(max(round(c + eps), 1), 1000)
	print(a, b)
