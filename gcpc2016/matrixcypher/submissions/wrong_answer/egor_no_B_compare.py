# given matrix [A,B;C,D] for 1-bit we get C'=C, D'=C+D and for 0-bit we get C'=C+D, D'=D
# so compare C and D and thus reconstruct the last bit
# to keep score when to stop, observe also B (if C=0 and B=0, then we are done)
# but this solution only watches C  and stops too early

input()#skip A,B
C,D=list(map(int, input().split()))

result=""

while C:
    if C<D:
        D=D-C
        result="1"+result
    else:
        C=C-D
        result="0"+result
  
print(result)


