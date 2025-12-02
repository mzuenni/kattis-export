#!/usr/bin/python3
import sys

n = int(sys.argv[1])
# tight mode: use sqrt(2) growth factor instead of 2
tight = int(sys.argv[2])

l = 1
if tight:
    while l < n // 4:
        l *= 2**0.5
    l = int(l)
else:
    while l < n:
        l *= 2

print(1)
print(n)

if tight:
    ps = [(2 * l, 2 * l)]
else:
    ps = [(l, l)]

layer = 0

while True:
    layer += 1

    if tight:
        l = int(l / 2**0.5)
    else:
        l //= 2
    # print("layer", layer, "length", l, "points", len(ps))

    nps = []
    for px, py in ps:
        if layer % 2 == 0:
            ax = px - l
            ay = py
            bx = px + l
            by = py
        else:
            ax = px
            ay = py - l
            bx = px
            by = py + l
        print(ax, ay, bx, by)
        nps.append((ax, ay))
        nps.append((bx, by))
        n -= 1
        if n == 0:
            sys.exit(0)
    ps = nps
