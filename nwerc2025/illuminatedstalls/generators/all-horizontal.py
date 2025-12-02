import sys, random

random.seed(sys.argv[1])

n = 200_000
a = []

mx = {}
for i in range(n):
    while True:
        y = random.randint(0, 10**9)
        x1 = random.randint(0, 10**9)
        x2 = random.randint(0, 10**9)
        if x1 > x2:
            x1, x2 = x2, x1

        if y in mx and mx[y] >= x1:
            continue

        mx[y] = x2
        a.append([x1, y, x2, y])
        break

if int(sys.argv[2]):
    for i in range(n):
        a[i][0], a[i][1] = a[i][1], a[i][0]
        a[i][2], a[i][3] = a[i][3], a[i][2]

print(1)
print(n)
for e in a:
    print(*e)
