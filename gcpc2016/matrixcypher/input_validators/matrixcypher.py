# checks 

def check_int(z, label):
    if z<0 and z>(2**128-1):
        print("number", label,"is wrong")
        exit(2)

A,B=list(map(int, input().split()))
C,D=list(map(int, input().split()))

check_int(A, "A")
check_int(B, "B")
check_int(C, "C")
check_int(D, "D")

if A==0:
    print("A=0")
    exit(3)

if D==0:
    print("D=0")
    exit(4)
    
cnt=0

while B or C:
    if C<D:
        D=D-C
        B=B-A
    else:
        C=C-D
        A=A-B
    cnt+=1

if cnt>120:
    print("Too long!")
    exit(5)
if A!=1 or B!=0 or C!=0 or D!=1:
    print("wrong start matrix")
    exit(6)
    
print("Ok")   
exit(42)


    
  

