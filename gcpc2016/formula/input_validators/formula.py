#checks that point are not collinear
       
def minus(a,b):
    return [x-y for x,y in zip(a,b)]
       
def cross(a,b):
    return  a[0]*b[1]-a[1]*b[0]
 
#main:   
p1, p2, p3 = [list(map(float, input().split())) for _ in range(3)]
R = float(input())

area=abs(cross(minus(p2,p1), minus(p3,p1)))

if area < 0.1:#because of the integer coordinates precise
    print("wrong!")
    exit(2)# on the same line!

print("ok!")
exit(42)
