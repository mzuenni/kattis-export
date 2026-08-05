from math import *

ps = []
for i in range(3):
    l = input().split()
    ps += [(float(l[0]), float(l[1]))]

s = 0
ls = [0, 0, 0]
for i in range(3):
    ls[i] = sqrt((ps[i][0] - ps[(i+1)%3][0])*(ps[i][0] - ps[(i+1)%3][0]) + (ps[i][1] - ps[(i+1)%3][1])*(ps[i][1] - ps[(i+1)%3][1]))
    s += ls[i]

s /= 2
prod = 1
for x in ls:
    prod *= s - x

r = sqrt(prod / s)
mess = float(input())
print(("%.3f" % (100 * (r - mess) / mess)))
