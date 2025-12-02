import sys, random

n = int(sys.argv[1])
assert n % 6 == 4
print(1)
print(n)
X = 200 if n < 100 else 10**9

Y = 200 if n < 100 else 10**8
if not int(sys.argv[2]):
    Y = 0

rot = int(sys.argv[3])
random.seed(n + 10 * Y + rot)


a = []

a.append((0, 0, X, 0))
a.append((0, 4, X - Y, 4))

a.append((X, 0, X, X))
a.append((X - 4, Y, X - 4, X))

offset = 0
for i in range(n // 12):
    a.append([1 + offset, 0, 1 + offset, 2])
    a.append([1 + offset, 2, 2 + offset, 2])
    a.append([2 + offset, 2, 2 + offset, 4])

    a.append([6 + offset, 0, 6 + offset, 2])
    a.append([5 + offset, 2, 6 + offset, 2])
    a.append([5 + offset, 2, 5 + offset, 4])

    offset += 10

offset = X - 10
for i in range(n // 12):
    a.append([X - 4, 1 + offset, X - 2, 1 + offset])
    a.append([X - 2, 1 + offset, X - 2, 2 + offset])
    a.append([X - 2, 2 + offset, X, 2 + offset])

    a.append([X - 4, 6 + offset, X - 2, 6 + offset])
    a.append([X - 2, 5 + offset, X - 2, 6 + offset])
    a.append([X - 2, 5 + offset, X, 5 + offset])

    offset -= 10

random.shuffle(a)
for r in range(rot):
    b = []
    for x1, y1, x2, y2 in a:
        b.append([y1, -x2, y2, -x1])

    for i in range(2):
        mn = min(min(e[i], e[i + 2]) for e in b)
        for j in range(n):
            b[j][i] -= mn
            b[j][i + 2] -= mn

    a = b

for e in a:
    print(*e)
