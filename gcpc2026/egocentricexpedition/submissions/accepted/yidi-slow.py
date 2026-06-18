def sub(x, y):
    return (x[0] - y[0], x[1] - y[1])

def cross(x, y):
    return (x[0] * y[0] + x[1] * y[1], x[0] * y[1] - x[1] * y[0])[1]

def length(x):
    return (x[0]*x[0] + x[1]*x[1]) ** 0.5

def distToLine(a, b, p):
    return abs(cross(sub(p, a), sub(b, a))) / length(sub(b, a))

T = int(input())
for t in range(T):
    print("? 0 1", flush=True)
    d1 = float(input())
    print("? 1 1", flush=True)
    d2 = float(input()) * 0.5**0.5

    p1 = (0, d1)
    p2 = (d2, d2)

    d = distToLine(p1, p2, (0, 0))
    A = d*d*4
    assert(abs(round(A) - A) < 1e-7)
    print("!", int(round(A)), flush=True)
