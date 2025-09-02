'''
Created on 19.05.2017

@author: Moritz Fuchs, Christian Mueller
'''
from decimal import *

def gcd(a,b):
    while b:
        a,b = b, a%b
    return a

def PolygonArea(corners):
    n = len(corners) # of corners
    area = Decimal(0)
    for i in range(n):
        j = (i + 1) % n
        area += corners[i][0] * corners[j][1]
        area -= corners[j][0] * corners[i][1]
    area = Decimal(abs(area)) / Decimal(2.0)
    return area

corners = []

n = int(raw_input())
for _ in range(n):
    x,y = map(int,raw_input().split())
    corners.append((x,y))
p = len(corners)
for i in range(n):
    p += gcd(abs(corners[i][0] - corners[(i+1)%n][0]), abs(corners[i][1] - corners[(i+1)%n][1]))-1
print(int(PolygonArea(corners) - Decimal(p)/Decimal(2) +Decimal(1)))
