t = int(input())

for _ in range(t):
	k=int(input())
	req = 0
	def read(x):
		global req
		x = int(x)
		req += x // k
		return x % k
	a,b,c,ab,bc,ac,abc = map(read, input().split())

	res = 9
	def test(s,p,a):
		global res
		cur = 0
		carry = 0
		for i in [0,1,2]:
			carry += s[i]
			x = (carry + k - 1) // k
			carry += p[i] - k * x
			if carry < 0:
				a = max(0, a+carry)
				carry = 0
			cur += carry // k + x
			carry %= k
		cur += (carry + a + k - 1) // k
		res = min(res, cur)

	test([a,b,c],[ab,bc,ac],abc)
	test([b,c,a],[bc,ac,ab],abc)
	test([c,a,b],[ac,ab,bc],abc)
	test([a,c,b],[ac,bc,ab],abc)
	test([c,b,a],[bc,ab,ac],abc)
	test([b,a,c],[ab,ac,bc],abc)

	print(req+res)
