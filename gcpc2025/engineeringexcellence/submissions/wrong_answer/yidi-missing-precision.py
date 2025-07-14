from math import pi as PI

EPS = 1e-7

def plus(a, b):
    return (a[0]+b[0], a[1]+b[1])

def minus(a, b):
    return (a[0]-b[0], a[1]-b[1])

def cross(a, b):
    return a[0] * b[1] - a[1] * b[0]

def cross2(a, b, c):
    return cross(minus(b, a), minus(c, a))

def dot(a, b):
    return a[0] * b[0] + a[1] * b[1]

def dot2(a, b, c):
    return dot(minus(b, a), minus(c, b))

def norm(a):
    return dot(a, a)

def rotate90(a):
    return (-a[1], a[0])

def lineIntersection(a, b, c, d):
    x = cross(minus(b, a), minus(d, c))
    y = cross(minus(c, a), minus(d, c))
    z = minus(b, a)
    return plus(a, (y/x*z[0], y/x*z[1]))

def distToLine(a, b, p):
    if a == b:
        return 1e9
    return abs(cross(minus(p, a), minus(b, a))) / (norm(minus(b, a))**0.5)

def circleRayIntersection(center, r, orig, di):
    a = norm(di)
    b = 2 * dot(di, minus(orig, center))
    c = norm(minus(orig, center)) - r*r
    discr = b*b - 4 * a *  c
    if discr >= 0:
        t1 = -(b + discr**0.5) / (2*a)
        t2 = -(b - discr**0.5) / (2*a)
        return [(orig[0] + t1*di[0], orig[1] + t1*di[1]), (orig[0] + t2*di[0], orig[1] + t2*di[1])]
    return []


n = int(input())
a = []
for i in range(n):
    x, y = map(int, input().split())
    a.append((x, y))

for i in range(4):
    a.append(a[i])

ans = 0
for i in range(2, n+2):
    center = ((a[i-1][0] + a[i+1][0])/2, (a[i-1][1] + a[i+1][1])/2)
    rad = norm(minus(center, a[i-1]))**0.5

    orig_len = norm(minus(a[i], a[i-1]))**0.5 + norm(minus(a[i], a[i+1]))**0.5

    def valid(p):
        def get(j):
            if i == j:
                return p
            else:
                return a[j]

        for j in range(i-2, i+1):
            if distToLine(get(j), get(j+1), get(j+2)) > EPS and cross2(get(j), get(j+1), get(j+2)) < -EPS: return False

            mid = plus(get(j), get(j+2))
            mid = (mid[0]/2, mid[1]/2)
            if norm(minus(get(j+1), mid)) > norm(minus(get(j), mid)) + EPS: return False

        return True

    def attempt(p):
        if valid(p):
            global ans
            ans = max(ans, norm(minus(p, a[i-1]))**0.5 + norm(minus(p, a[i+1]))**0.5 - orig_len)

    attempt(plus(center, rotate90(minus(a[i-1], center))))

    lines = []
    lines.append((a[i-2], a[i-1]))
    lines.append((a[i-1], plus(a[i-1], rotate90(minus(a[i-1], a[i-2])))))

    lines.append((a[i+2], a[i+1]))
    lines.append((a[i+1], plus(a[i+1], rotate90(minus(a[i+1], a[i+2])))))

    if abs(cross(minus(lines[0][1], lines[0][0]), minus(lines[2][1], lines[2][0]))) > EPS:
        attempt(lineIntersection(lines[0][0], lines[0][1], lines[2][0], lines[2][1]))

    for x, y in lines:
        for p2 in circleRayIntersection(center, rad, x, minus(y, x)):
            attempt(p2)


print(f"{ans:.12f}")
