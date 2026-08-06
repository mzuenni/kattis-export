#!/usr/bin/env python

from os import linesep
from sys import stdin,exit
from re import search

def readints() :
    return (int(x) for x in stdin.readline().split())

def readfloats() :
    return (float(x) for x in stdin.readline().split())

def readlist() :
    array = stdin.readline().split()
    assert (int(array[0])+1==len(array))
    return array[1:]

T, = readints()
for tt in xrange(T):
    N,l,t = readints()
    assert (1 <= N <= 100)
    assert (0 <= l <= (N-1)**2)
    assert (0 <= t <= 5000)
    uu = list(readfloats())
    assert (len(uu)==N)
    for u in uu:
        assert (0 <= u <= 1000)
    for i in xrange(l):
        sj,tj,pj = stdin.readline().split()
        sj = int(sj)
        tj = int(tj)
        pj = float(pj)
        assert (0 <= sj < N)
        assert (0 <= tj < N)
        assert (0 < pj <= 1)
    
exit(42)
