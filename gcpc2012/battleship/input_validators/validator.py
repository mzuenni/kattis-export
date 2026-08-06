#!/usr/bin/env python

from os import linesep
from sys import stdin,exit
from re import search

def readints() :
    return (int(x) for x in stdin.readline().split())

T = int(stdin.readline())
assert(0 < T <= 20)
for t in xrange(T) :
    w,h,n = readints()
    assert(1 <= w <= 30)
    assert(1 <= h <= 30)
    assert(1 <= n <= 2000)
    for i in xrange(2*h) :
        s = stdin.readline().rstrip(linesep)
        assert(len(s)==w)
        assert(search('^[_#]*$',s))
    for i in xrange(n) :
        x,y = readints()
        assert(0 <= x < w)
        assert(0 <= y < h)
exit(42)
