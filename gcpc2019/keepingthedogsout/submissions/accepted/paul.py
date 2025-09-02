from fractions import gcd
from collections import Counter
import sys

# Miller-Rabin primality test
def is_prime(n):
    if n < 2: return False
    if n%2 == 0: return n == 2
    s = 0; d = n-1
    while d%2 == 0:
        d /= 2; s += 1
    for a in range(2,min(50,n)):
        p = pow(a,d,n)
        if p == 1: continue
        for _ in range(s-1):
            if p == n-1: break
            p = (p*p) % n
        if p != n-1: return False
    return True

# Integer factorization using Pollard's rho algorithm
def pollard(n):
    if n%2 == 0: return 2
    def f(x): return (x*x+1) % n
    for i in range(2,n):
        x = i; y = f(i)
        while gcd(n+y-x,n) == 1:
            x = f(x); y = f(f(y))
        g = gcd(n+y-x,n)
        if g != n: return g
    return -1

def factorize(n):
    if n == 1: return []
    if is_prime(n): return [n]
    x = pollard(n)
    return factorize(x) + factorize(n/x)

# Generate a list of all divisors
def divisors(n):
    divs = [1]
    for p,e in Counter(factorize(n)).most_common():
        divs = [x * (p**i) for x in divs for i in range(e+1)]
    return divs

n = int(raw_input())
stones = map(int, raw_input().split(' '))
area = sum([a * 4**i for i,a in enumerate(stones)])

for height in divisors(area):
    width = area/height

    total = 0
    possible = True
    for i in reversed(range(n+1)):
        total = 4*total + stones[i]
        if total > (height >> i) * (width >> i):
            possible = False

    if possible:
        print('%d %d' % (height,width))
        sys.exit(0)

print('impossible')
