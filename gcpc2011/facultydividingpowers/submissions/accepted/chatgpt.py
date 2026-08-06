import sys

MAX = 10 ** 6

# Sieve of Eratosthenes
is_prime = [True] * (MAX + 1)
is_prime[0] = is_prime[1] = False
primes = []

for i in range(2, MAX + 1):
    if is_prime[i]:
        primes.append(i)
        if i * i <= MAX:
            for j in range(i * i, MAX + 1, i):
                is_prime[j] = False

def factorize(x):
    res = []
    for p in primes:
        if p * p > x:
            break
        if x % p == 0:
            cnt = 0
            while x % p == 0:
                x //= p
                cnt += 1
            res.append((p, cnt))
    if x > 1:
        res.append((x, 1))
    return res

def legendre(n, p):
    cnt = 0
    while n:
        n //= p
        cnt += n
    return cnt

def solve():
    input = sys.stdin.readline

    t = int(input())
    for _ in range(t):
        n, k = map(int, input().split())

        ans = 10 ** 30
        for p, e in factorize(k):
            ans = min(ans, legendre(n, p) // e)

        print(ans)

solve()
