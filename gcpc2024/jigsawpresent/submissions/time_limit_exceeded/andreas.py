#!/bin/python3

def print_sol(enc1, enc2, n):
	print("no")
	a = []
	b = []

	ki = 0 
	for ni in range(n//2):
		if (enc1[0] & (1 << ni)):
			if (enc1[1] & (1 << ki)):
				b.append(str(ni + 1)) 
			else:
				a.append(str(ni + 1)) 
			ki += 1
	
	ki = 0 
	for ni in range(n-n//2):
		if (enc2[0] & (1 << ni)):
			if (enc2[1] & (1 << ki)):
				a.append(str(ni + n//2 + 1)) 
			else:
				b.append(str(ni + n//2 + 1)) 
			ki += 1

	print(len(a), end=' ')
	print(' '.join(a))
	print(len(b), end=' ')
	print(' '.join(b))

def brute(L, R, x):
	ret = { (0, 0): (0, 0) }
	val = { (0, 0): (0, 0) }

	n = R - L
	ni = -1
	for i in range(1, 1 << n):
		k = bin(i).count("1")
		if k == 1:
			ni += 1
		prev_set = i - (1 << ni)

		for j in range(1 << k):
			prev_j = j & ((1 << (k-1)) - 1)
			current = val[(prev_set, prev_j)]

			nxt = x[ni + L]
			if prev_j != j:
				nxt = (nxt[0] * (-1), nxt[1] * (-1))
			current = (current[0] + nxt[0], current[1] + nxt[1])

			ret[current] = (i, j)
			val[(i, j)] = current
	return ret

def solve():
	n = int(input())
	x = []
	for _ in range(n):
		a, b = map(int, input().split())
		x.append((a, b)) 
		
	n = min(n, 28) 

	A = brute(0, n//2, x)
	B = brute(n//2, n, x)

	found = False
	for s in A:
		if s == (0, 0):
			continue
		if s in B:
			print_sol(A[s], B[s], n)
			found = True
			break
	if not found:
		print("yes")

solve()

