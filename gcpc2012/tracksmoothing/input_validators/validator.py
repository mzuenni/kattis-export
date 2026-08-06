#!/usr/bin/env python

from os import linesep
from sys import stdin,exit
from re import search

def readints() :
    return (int(x) for x in stdin.readline().split())

def readlist() :
    array = stdin.readline().split()
    assert (int(array[0])+1==len(array))
    return array[1:]

def cross(v,w) :
    return v[0]*w[1]-w[0]*v[1]

def left(a,b,c) :
    v=[b[i]-a[i] for i in range(2)]
    w=[c[i]-b[i] for i in range(2)]
    return cross(v,w)>=0

def check_ccw(polygon) :
    for i in xrange(len(polygon)) :
        assert (left(polygon[i-2],polygon[i-1],polygon[i]))

T, = readints()
assert(0 < T <= 100)
for t in xrange(T) :
    r,n = readints()
    assert(0 <= r <= 1000)
    assert(3 <= n <= 10000)
    polygon = []
    for i in xrange(n) :
        x,y = readints()
        assert (-10000 <= x <= 10000)
        assert (-10000 <= y <= 10000)
        polygon.append([x,y])
    check_ccw(polygon)
exit(42)
