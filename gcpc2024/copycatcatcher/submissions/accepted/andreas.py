#!/bin/python3

N = 2500
A = 53
B = 1000000007
p = []

maxcid = N+1
id_of_const = dict()

def calc_p():
	p.append(1)
	for _ in range(N-1):
		p.append(p[-1]*A % B)

def matches(a, b):
	n = len(a)
	m = len(b)

	if m > n:
		return False
	for i in range(n-m+1):
		if b[m-1] == a[i][m-1]:
			return True
	return False

def h(lst):
	if len(lst) == 0:
		return []

	res = [lst[0]]*len(lst)
	for i in range(1, len(lst)):
		res[i] = (res[i-1]*A + lst[i]) % B

	return res

def parse(n, s, j):
	global maxcid
	pos = dict()
	res = []

	for i in range(j, n):
		t = s[i]

		if len(t) == 1 and t.isalpha():
			diff = 0 if t not in pos else i-pos[t]
			pos[t] = i
			res.append(diff)
		else:
			if t not in id_of_const:
				id_of_const[t] = maxcid
				maxcid += 1
			res.append(id_of_const[t])

	return res

def read(ref=False):
	n = int(input())
	s = input().split()

	tokens = []
	tokens.append(parse(n, s, 0))
	if ref:
		for i in range(1, n):
			tokens.append(parse(n, s, i))

	ret = list(map(h, tokens))
	return ret

calc_p()
ref = read(ref=True)
q = int(input())
for _ in range(q):
	s = read()[0]
	print("yes") if matches(ref, s) else print("no")
