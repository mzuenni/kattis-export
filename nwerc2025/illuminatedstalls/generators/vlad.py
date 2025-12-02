

a = []


for i in range(2):
    x = 0
    y = 10**8 * i

    a.append([0, y, 10**9, y])

    def f(dx, dy):
        if len(a) == 200_000:
            return
        global x, y
        if dx + dy > 0:
            a.append([x, y, x+dx, y+dy])
        else:
            a.append([x+dx, y+dy, x, y])

        x += dx
        y += dy

    for k in range(22_359):
        f(0, 2+k)
        f(1+k, 0)
        f(0, 2+k)
        f(3+k, 0)
        f(0, -2-k)
        f(1+k, 0)
        f(0, -2-k)
        x += 3+k

print(1)
print(len(a))
for e in a:
    print(*e)
