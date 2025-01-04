N, M, C = 28, 13, 4100
vis = [{} for i in range((2 * C + 1) * M)]
a = []

def finish(*args):
	print("no")
	for msk in args:
		print(bin(msk).count("1"), end = " ")
		for i in range(N):
			if (msk >> i) % 2 == 1:
				print(i + 1, end = " ")
		print()
	exit(0)

def dfs(x, y, m, f, mskL, mskR):
	if x == 0 and y == 0: finish(mskL, mskR)
	if m < 0 and f == 0:
		vis[x + M * C][y] = (mskL, mskR)
		return
	if m < M and f == 1:
		for s in [-1, 1]:
			i = s * x + M * C
			if 0 <= i < (2 * C + 1) * M and s * y in vis[i]:
				u, v = vis[i][s * y]
				if s == -1:
					u, v = v, u
				finish(mskL | v, mskR | u)
		return
	dfs(x, y, m - 1, f, mskL, mskR)
	dfs(x + a[m][0], y + a[m][1], m - 1, f, mskL | (2**m), mskR)
	dfs(x - a[m][0], y - a[m][1], m - 1, f, mskL, mskR | (2**m))

n = min(int(input()), N)
for i in range(n):
	y, x = map(int, input().split(' '))
	a += [(x, y)]
	dfs(x, y, i - 1, i >= M, 2**i, 0)
print("yes")