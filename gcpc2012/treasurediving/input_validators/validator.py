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

T, = readints()
assert(0 < T <= 2000)
for t in xrange(T) :
    n,m = readints()
    assert(1 <= n <= 10000)
    assert(1 <= m <= 50000)
    for j in xrange(m) :
        a,b,l = readints()
        assert (0 <= a < n)
        assert (0 <= b < n)
        assert (0 <= l <= 500)
    i, = readints()
    idols = list(readints())
    assert (len(idols) == i)
    for p in idols :
        assert (0 <= p < n)
    a, = readints()
    assert (0 <= a <= 1e6)
exit(42)
