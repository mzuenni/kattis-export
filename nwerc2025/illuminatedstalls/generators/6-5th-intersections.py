import sys

n = int(sys.argv[1])
assert(n % 5 == 1)
print(1)
print(n)
print(0, 0, 10**9, 0)

OFFSET = 0
for i in range(n // 5):
    print(OFFSET + 1, 0, OFFSET + 1, 3)
    print(OFFSET + 1, 3, OFFSET + 2, 3)
    print(OFFSET + 2, 3, OFFSET + 2, 4)
    print(OFFSET + 2, 4, OFFSET + 5, 4)
    print(OFFSET + 5, 0, OFFSET + 5, 4)

    OFFSET += 10
