t = int(input())

b = 0
x = 0
y = 0
if t > 6 * 60:
    b += max(0, min(30, t - 6 * 60))
    t -= b
if t > 9 * 60:
    x = max(0, min(15, t - 9 * 60))
    t -= x
if t > 10 * 60:
    y = max(0, t - 10 * 60)

print(b + x + y)