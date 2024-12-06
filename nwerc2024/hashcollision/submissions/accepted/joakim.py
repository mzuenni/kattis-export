#!/usr/bin/env python3
n = int(input())
def query(c, r, typ = '?'):
    print(typ, c, r)
    return int(input()) if typ == '?' else exit()
x = query(n,n)
query(x,query(n-x,n),'!') if x < n else query(n,n,'!')
