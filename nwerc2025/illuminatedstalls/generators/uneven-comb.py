print(1)
print(42_915 * 4)

a = 21344
b = 31013

for R in range(4):
    x = 0
    y = R * 10**7

    X = 10**9
    print(0, y, X, y)
    for i in range(b // 2):
        print(x, y, x, y + b + 1)
        x += b + 2

    print(x, y, x, y + a)
    x += 2
    for i in range(a // 2 - 1):
        print(x, y, x, y + 1)
        x += 2

    print(x, y, x, y + b)
    x += b + 2

    while x <= X:
        print(x, y, x, y + b + 1)
        x += b + 2
