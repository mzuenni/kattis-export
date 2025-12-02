import sys

flipped = int(sys.argv[1])
ans = int(sys.argv[2])

X = 10**9
x = X // 2 + 10 ** 5

a = []
p = 0
a.append([0, 0, X, 0])
while x > 2 * 10**5:
    a.append([p, 0, p, x])
    a.append([X-p, 0, X-p, x])
    assert(X-2*p > x)
    x = x // 2
    p += x + 1

p = X // 2
if ans:
    a.append([p, 0, p, 1])

p -= 1
while len(a) + 2 < 2 * 10**5:
    a.append([p, 0, p, 1])
    a.append([X-p, 0, X-p, 1])
    p -= 2

if flipped:
    for i in range(len(a)):
        a[i][0], a[i][1] = a[i][1], a[i][0]
        a[i][2], a[i][3] = a[i][3], a[i][2]

print(1)
print(len(a))
for e in a:
    print(*e)
