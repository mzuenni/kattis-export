import sys

n = int(sys.argv[1])
assert n % 6 == 2
print(1)
print(n)
X = 200 if n < 100 else 10**9
print(0, 0, X, 0)
print(0, 4, X, 4)

offset = 0
for i in range(n // 6):
    print(1 + offset, 0, 1 + offset, 2)
    print(1 + offset, 2, 2 + offset, 2)
    print(2 + offset, 2, 2 + offset, 4)

    print(6 + offset, 0, 6 + offset, 2)
    print(5 + offset, 2, 6 + offset, 2)
    print(5 + offset, 2, 5 + offset, 4)

    offset += 10
