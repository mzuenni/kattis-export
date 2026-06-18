n, k = map(int, input().split())

res = ''
for _ in range(k):
    res += 'a'

nxt = "bcd" * (n+k)
for j in range(n-k):
    res += nxt[j]

print(res)
