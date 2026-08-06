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
assert (1 <= T <= 20)
for t in xrange(T):
    m,n = readints()
    assert (1 <= m <= 1e9)
    assert (1 <= n <= 1e5)
    for i in xrange(n):
        x,y = readints()
        assert (0 <= x < m)
        assert (0 <= y < m)

exit(42)
