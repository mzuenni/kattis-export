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
assert (1 <= T <= 1000)
for t in xrange(T):
    t1 = list(readints())
    t2 = list(readints())
    assert (len(t1)==9)
    assert (len(t2)==9)
    for x in t1+t2:
        assert (-1000 <= x <= 1000)
    
exit(42)
