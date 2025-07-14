t = int(input())

if t <= 6 * 60:
    print(0)
elif t <= 6 * 60 + 30:
    print(t - 6 * 60)
elif t <= 9 * 60 + 30:
    print(30)
elif t <= 9 * 60 + 45:
    print(t - 9 * 60)
elif t <= 10 * 60 + 45:
    print(45)
else:
    print(t - 10 * 60)
