#!/usr/bin/env python3
"""
We make a hamiltonian path from
111111100000
to
000001111111 recursively

start with
'1' x a + '0' x b
if a==0 or b==0: path = trivial
if a==1: do 1000 0100 0010 0001
a x '1' + (b-1) x '0' + '0'
recursive on s[:-1]
(b-1) x '0' + a x '1' + '0'
(b-1) x '0' + (a-1) x '1' + '01' ([-3] to [-2])
recursive on s[:-2][::-1]
(a-1) x '1' + (b-1) x '0' + '01'
(a-2) x '1' + b x '0'     + '11'
recursive on s[:-2]
b x '0' + a x '1' 

Only need to write rankof and kth (both 0-based)
"""

from functools import cache
from math import comb

@cache
def ways(a,b):
    return comb(a+b,b)
def rankof(s):
    a,b=s.count('1'),s.count('0')
    if a==0 or b==0: return 0
    if a==1: return s.index('1')
    if s[-1]=='0': return rankof(s[:-1])
    ans=ways(a,b-1)
    if s[-2]=='0':
        return ans+rankof(s[:-2][::-1])
    return ans + ways(a-1,b-1) + rankof(s[:-2])
def kth(k,a,b):
    if a<=1 or b==0: return k*'0' + a*'1' + (b-k)*'0'
    c = ways(a,b-1)
    if k<c: return kth(k,a,b-1)+'0'
    k-=c
    c = ways(a-1,b-1)
    if k<c: return kth(k,a-1,b-1)[::-1]+'01'
    return kth(k-c,a-2,b)+'11'


for _ in range(int(input())):
    h,w,k = map(int,input().split())
    s = ''.join(input() for i in range(h)).replace('.','0').replace('#','1')
    if comb(h*w,s.count('0'))%2:
        print("risky")
    else:
        k = rankof(s)
        k^=1
        t = kth(k,s.count('1'),s.count('0'))
        for i,(a,b) in enumerate(zip(s,t)):
            if a!=b:
                if a=='1': x=i
                else: y=i
        print(1+x//w,1+x%w)
        print(1+y//w,1+y%w)
        
