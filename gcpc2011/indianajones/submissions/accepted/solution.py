import sys

for _ in range(int(input())):
	n, h = map(int, input().split())
	adj = [[] for _ in range(n)]
	ind = [0 for _ in range(n)]
	for _ in range(h):
		u, v = map(int, sys.stdin.readline().split())
		u -= 1
		v -= 1
		adj[u].append(v)
		ind[v] += 1
	seq = []
	for i in range(n):
		if ind[i] == 0: seq.append(i)
	j = 0
	unique = True
	while j < len(seq):
		if len(seq) - j > 1: unique = False
		u = seq[j]
		j += 1
		for v in adj[u]:
			ind[v] -= 1
			if ind[v] == 0: seq.append(v)
	if len(seq) < n: print('recheck hints')
	elif not unique: print('missing hints')
	else: sys.stdout.write(' '.join(str(i+1) for i in seq) + '\n')
