M,s=input()+input(),input()
s=s[(x:=max(s.find("12"),s.find("02"))+1):]+s[:x]
if(x:=s.rfind('2'))+1:s='0'*x+'1'+s[x+1:]
if M[0]>'D':s='2'*(x:=s.find('1')+1)+s[x:]
print(s)
