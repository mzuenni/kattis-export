import sys
input = sys.stdin.readline
sys.setrecursionlimit(2000000)
N, C, K, P, B = 3 * 10**5 + 5, 27, 3, [10**9 + 7, 10**9 + 9, 10**9 + 21], [123456789, 987654321, 543212345]
M, lnk, val, par, hash, go = 1, [-1] * N, [0] * N, [-1] * N, [[0] * K for _ in range(N)], [[0] * C for _ in range(N)]

def get_link(k):
	if lnk[k] == -1:
		lnk[k] = 0 if k == 0 or par[k] == 0 else walk(get_link(par[k]), val[k])
	return lnk[k]

def walk(k, c):
	if go[k][c] == 0:
		return 0 if k == 0 else walk(get_link(k), c)
	return go[k][c]

def match(s):
	k, res = 0, [0] * K
	for c in s:
		k = walk(k, 0 if c == ' ' else ord(c) - ord('a') + 1)
		for i in range(K):
			res[i] += hash[k][i] - P[i] * (res[i] + hash[k][i] >= P[i])
	return res == [0] * K

def insert(s):
	global M
	u = 0
	for c in s:
		c = 0 if c == ' ' else ord(c) - ord('a') + 1
		if go[u][c] == 0:
			go[u][c] = M
			par[M] = u
			val[M] = c
			M += 1
		u = go[u][c]
	return u

n, m, k = map(int, input().split())
fin, cur = [insert(input().strip()) for _ in range(n)], [1] * K
for _ in range(m):
	a, b = map(lambda x: fin[int(x) - 1], input().split())
	for i in range(K):
		cur[i] = cur[i] * B[i] % P[i]
		hash[a][i] -= cur[i] - P[i] * (hash[a][i] - cur[i] < 0)
		hash[b][i] += cur[i] - P[i] * (hash[b][i] + cur[i] >= P[i])
sys.stdout.write("\n".join(["yes" if match(input().strip()) else "no" for _ in range(k)]))