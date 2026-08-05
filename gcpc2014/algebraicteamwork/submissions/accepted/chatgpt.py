MOD = 10**9 + 7
MAXN = 100000

fact = [1] * (MAXN + 1)
for i in range(1, MAXN + 1):
    fact[i] = fact[i - 1] * i % MOD

t = int(input())
for _ in range(t):
    n = int(input())
    print((fact[n] - 1) % MOD)
