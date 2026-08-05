#uses heron formula to calculate the area
import math

def length(a,b):
    return math.sqrt(sum([(x-y)**2 for x,y in zip(a,b)]))

#main:
p1, p2, p3 = [list(map(float, input().split())) for _ in range(3)]
R = float(input())

a,b,c= length(p1, p2), length(p2, p3), length(p3,p1)
p=(a+b+c)*0.5

r=math.sqrt((p-a)*(p-b)*(p-c)/p)

print((r-R)/R*100.0)

