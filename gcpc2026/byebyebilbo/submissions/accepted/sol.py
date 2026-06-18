n, k = map(int, input().split(" "))
p = [0] + list(map(int, input().split(" "))) if k > 1 else [0]
s, d = [1], [0] * n
for i in range(n - 1, 0, -1):
	if d[i] == k - 1:
		s += [i+1]
	else:
		d[p[i]-1] = max(d[p[i]-1], d[i] + 1)
print(len(s))
print(*s)