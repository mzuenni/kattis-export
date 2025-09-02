from fractions import gcd
from collections import Counter

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

# Convert a polynomial into a base B number
def convert_to_base(p,B):
    for i in range(len(p)-1):
        p[i+1] += p[i]/B
        p[i] %= B
    return p

def read_poly():
    return [int(a) for a in raw_input().split(' ')[:0:-1]]

def mult_poly(a,b):
    ab = [0]*(len(a)+len(b))
    for i,u in enumerate(a):
        for j,v in enumerate(b):
            ab[i+j] += u*v
    return ab

# Multiply the first two numbers as polynomials.
# If a base exists, it must be a divisor of the first
# non-zero coefficient in the difference of a*b and c.
def find_base():
    a, b, c = [read_poly() for _ in range(3)]
    ab = mult_poly(a,b)
    
    # Pad with zeroes
    n = max(len(c),len(ab)) + 2
    ab, c = [p + [0]*(n-len(p)) for p in ab, c]

    Bmin = max(a+b+c) + 1
    
    if ab == c:
        return Bmin
    
    # Find first difference between ab and c
    Bmult = filter(lambda x: x != 0, [u-v for (u,v) in zip(ab,c)])[0]
    if Bmult < 0: return None
    
    for B in divisors(Bmult):
        if B < Bmin: continue
        if convert_to_base(ab[:],B) == c:
            return B

    return None

res = find_base()
print(res if res != None else "impossible")
