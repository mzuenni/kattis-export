import random
import sys
import math
from decimal import Decimal, getcontext
getcontext().prec = 100

random.seed(int(sys.argv[1]))
MAXT = 10**4
MINA = 30**2
MAXA = 50**2

ang = []
for x in range(51):
    for y in range(51):
        if x + y == 0: continue
        if math.gcd(x, y) > 1: continue
        ang.append((Decimal(x), Decimal(y)))

ang.sort(key = lambda x : math.atan2(x[1], x[0]))

cnt = MAXT // len(ang)

def norm(vec):
    d = (vec[0]**2 + vec[1]**2).sqrt()
    return (vec[0] / d, vec[1] / d)

def trans(vec1, vec2, la):
    return (vec1[0] * la + vec2[0] * (1 - la), vec1[1] * la + vec2[1] * (1-la))

tests = []
for i in range(len(ang)):
    d1, d2 = norm(ang[i]), norm(ang[(i+1) % len(ang)])
    for j in range(cnt):
        la = Decimal(1) - (Decimal(j) / Decimal(cnt))
        d = norm(trans(d1, d2, la))
        r = Decimal(random.randint(MINA, MAXA) / Decimal(2)).sqrt()
        tests.append((d[0] * r, d[1] * r))

random.shuffle(tests)
print(len(tests))
for x, y in tests:
    print(format(x, ".30f"), format(y, ".30f"))
