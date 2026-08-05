# given matrix [A,B;C,D] for 1-bit we get C'=C, D'=C+D and for 0-bit we get C'=C+D, D'=D
# so compare C and D and thus reconstruct the last bit
# to keep score when to stop, observe also B (if C=0 and B=0, then we are done)
# but this solution only watches B  and stops too early

A,B=list(map(int, input().split()))
C,D=list(map(int, input().split()))

result=""

while B:
    if C<D:
        D=D-C
        B=B-A
        result="1"+result
    else:
        C=C-D
        A=A-B
        result="0"+result
  
print(result)


