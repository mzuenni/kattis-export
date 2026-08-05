
try:
    import builtins
    input = getattr(__builtin__, 'raw_input', input)  # Python 3 (PEP 3111)
except:
    pass


from math import *

a, N = input().split(" ")
a, N = float(a), int(N)

point = [input().split(" ") for _ in range(N)]
point = [(float(x), float(y)) for x, y in point]

def sub(a, b):
    return (a[0] - b[0], a[1] - b[1])

def dot(a, b):
    return a[0] * b[0] + a[1] * b[1]

def cross(a, b):
    return a[0] * b[1] - a[1] * b[0]

def length(a):
    return hypot(a[0], a[1])

convex_part = lambda i: abs(cross(sub(point[i-1], point[0]),
                                  sub(point[i],   point[0])))
convex_area = [convex_part(i) for i in range(2, N)]
convex_area = sum(convex_area) / 2

def cut_area(j):
    """calculate 1/2 * a_i/s * b_i/s * sin(angle).
       but assume s == 1 (divide result by s**2 for fix)"""
    i = (j - 1 + N) % N
    k = (j + 1) % N
    a, b = sub(point[i], point[j]), sub(point[k], point[j])
    len_ab = length(a) * length(b)
    angle = acos(dot(a, b) / len_ab)
    return sin(angle) * len_ab / 2

cut = [cut_area(i) for i in range(N)]

# A - sum(cut) / s**2 = a * A
s = sqrt(sum(cut) / (convex_area * (1-a)))
print(s)
