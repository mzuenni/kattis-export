import sys, random

random.seed(int(sys.argv[1]))
n = int(sys.argv[2])
bad = random.randint(0, n-1)
if len(sys.argv) > 3:
    bad = int(sys.argv[3])

while True:
    a = [random.randint(1, 50) for i in range(n)]
    b = [random.randint(1, 50) for i in range(n)]
    a[bad] = 0
    b[bad] = 0

    x = sum(a) - sum(b)
    if abs(x) >= 10 ** 3:
        continue

    if x < 0:
        a, b = b, a
    break

a[bad] = 1
b[bad] = 10**3

print(n)
for x, y in zip(a, b):
    print(x, y)
