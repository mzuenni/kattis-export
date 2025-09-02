import itertools
import math
import random

random.seed(238764)

N = 200000
K = int(math.log(N,2))

def create_case(i, n, k):
    name = '%02d-%d-%d' % (i,n,k)
    with open('../data/secret/' + name + '.in', 'w') as f:
        f.write('%d %d\n' % (n,k))

# some small cases:
for i, (n,k) in enumerate([(n,k) for n in range(1,6) for k in range (1,n+1)]):
    create_case(i+1, n, k)

# some cases with n maximal:
create_case(30,N,K)
create_case(31,N,K+1)
create_case(32,N,N)
create_case(33,N,1)

# some cases where abs(n - 2**k) is small:
for i, d in enumerate(range(-2,2) * 2):
    k = random.randint(10,K+1)
    create_case(40+i, 2**k + d, k)

# some more random cases:
for i in range(10):
    n = random.randint(1,N)
    k = random.randint(1,n)
    create_case(80+i, n, k)
