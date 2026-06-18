import string
import random

n, k = map(int, input().split())

res = ('a' * k) + 'b' + ''.join(random.choice(string.ascii_lowercase) for _ in range(n - k - 1))
print(res[:n])
