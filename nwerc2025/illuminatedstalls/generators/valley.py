import sys

n = int(sys.argv[1])
a = list(map(int, sys.argv[2:]))

print(1)
print(n)

X = 10 ** 9
print(0, 0, X, 0)
print(0, X, X, X)

B = (X-1) // (n-3)
for i in range(n-2):
    h = B - 1
    if i in a:
        h = X-1
    print(i*B, 0, i*B, h)
