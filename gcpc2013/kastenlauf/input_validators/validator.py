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
assert (T <= 50)
for t in xrange(T):
    n, = readints()
    assert(0 <= n <= 100)
    for i in xrange(n+2):
        x,y = readints()
        assert(-32768 <= x <= 32767)
        assert(-32768 <= y <= 32767)

exit(42)
