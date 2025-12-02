#!/usr/bin/env python3

h,w,k,i,t=map(int,input().split())
a='I'*i+'T'*~-t+'K'*k+'IT'
[print(a[i+1::h])for i in range(h)]
