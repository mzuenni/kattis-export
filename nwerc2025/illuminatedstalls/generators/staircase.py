import sys

n = int(sys.argv[1])
long = int(sys.argv[2])

print(1)
print(n)

H = (n-2) // 2 + 1
print(0, 0, H, 0)
print(0, 0, 0, H)

x = 0
y = H
for i in range(n-2):
    if i == 0:
        print(x, y, x+2, y)
        x += 2
    elif i == n-3:
        print(x, y-2, x, y)
    elif i % 2 == 0:
        if i == long:
            print(0, y, x+1, y)
        else:
            print(x, y, x+1, y)
        x += 1
    else:
        if i == long:
            print(x, 0, x, y)
        else:
            print(x, y-1, x, y)
        y -= 1
