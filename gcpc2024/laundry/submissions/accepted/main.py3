t = int(input())

for _ in range(t): 
	k=int(input())
	a,b,c,ab,bc,ac,abc = map(int, input().split())

	res = 10**10
	def test(s,p,a=abc):
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

	test([a,b,c],[ab,bc,ac])
	test([b,c,a],[bc,ac,ab])
	test([c,a,b],[ac,ab,bc])
	test([a,c,b],[ac,bc,ab])
	test([c,b,a],[bc,ab,ac])
	test([b,a,c],[ab,ac,bc])

	print(res)
