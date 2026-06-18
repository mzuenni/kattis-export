import argparse, sys, random

def rnd(l, r):
	return random.randint(l, r)

parser = argparse.ArgumentParser()
parser.add_argument('-t', choices=['random', 'line', 'star', 'binary', 'caterpillar'], required=True)
parser.add_argument('-n', type=int, required=True)
parser.add_argument('-k', type=int, required=True)
parser.add_argument('-seed', type=int, default=42)
args = parser.parse_args()

random.seed(args.seed)
n = args.n
k = args.k

if n == 1:
	print(f"{n} {k}")
	print()
	exit(0)

p = []

if args.t == 'line':
	p = [i for i in range(1, n)]
elif args.t == 'star':
	p = [1] * (n-1)
elif args.t == 'random':
	p = [rnd(1, i) for i in range(1, n)]
elif args.t == 'binary':
	p = [(i + 1) // 2 for i in range(1, n)]
elif args.t == 'caterpillar':
	l = rnd(2, n)
	p = [i for i in range(1, l)]
	for i in range(l, n):
		p.append(rnd(1, l - 1))

print(f"{n} {k}")
print(" ".join(map(str, p)))