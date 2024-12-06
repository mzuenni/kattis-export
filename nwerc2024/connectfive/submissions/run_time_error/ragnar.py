#!/usr/bin/env python3

n = 5
ps = set(tuple(map(int, input().split())) for _ in range(n))


def clamp(x, a, b):
    return max(a, min(b, x))


def solve(ps):
    l = len(ps)
    if len(ps) == 1:
        return 0
    if len(ps) == 2:
        return abs(ps[1][0] - ps[0][0]) + abs(ps[1][1] - ps[0][1])

    # As long as the min/max x/y is unique, shrink points to the 'inner box'.

    xs = sorted([p[0] for p in ps])
    ys = sorted([p[1] for p in ps])
    ans = xs[1] - xs[0] + xs[-1] - xs[-2] + ys[1] - ys[0] + ys[-1] - ys[-2]

    ps2 = set()
    interior = False
    for x, y in ps:
        x = clamp(x, xs[1], xs[-2])
        y = clamp(y, ys[1], ys[-2])
        ps2.add((x, y))
        if xs[1] < x < xs[-2] and ys[1] < y < ys[-2]:
            interior = True

    # If points 'merge', recurse.
    if len(ps2) < l:
        return ans + solve(ps2)

    # Otherwise, there are three cases where the solution is
    # to take the circumference of the inner box:
    #
    # 1. a rectangle
    # *...*
    # .....
    # *...*
    #
    # 2. rectangle + point on boundary, e.g.
    # *...*
    # .....
    # *.*.*
    #
    # 3. rectangle, but with 'missing corner', e.g.
    # *...*
    # ....*
    # *.*..
    #
    # In the last case, a square with interior point, one extra line is needed:
    # *...*
    # ..*..
    # *...*

    # Circumference of the square
    ans += 2 * (xs[-2] - xs[1]) + 2 * (ys[-2] - ys[1])
    # Add one 'bar'
    if interior:
        ans += min(xs[-2] - xs[1], ys[-2] - ys[1])

    return ans


print(solve(ps))
