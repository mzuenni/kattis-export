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
assert(0 < T <= 100)
for t in xrange(T) :
    l,s = readints()
    assert(1 <= l <= 10000)
    assert(1 <= s <= 10000)
    totallength=0
    for i in xrange(s) :
        p,suf = stdin.readline().split()
        p=int(p)
        totallength+=len(suf)
        assert(1 <= p <= l)
#        assert(p + len(suf) == l+1) # Do not be too smart!
        assert(search('^[A-Za-z.*]*$',suf))
    assert(totallength <= 500000) # Statement says 250k
exit(42)
