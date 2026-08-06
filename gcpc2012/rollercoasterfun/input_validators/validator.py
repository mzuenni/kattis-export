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

n, = readints()
assert(0 < n <= 100)
for i in xrange(n) :
    a,b,t = readints()
    assert(0 <= a <= 1000)
    assert(0 <= b <= 1000)
    assert(0 < t <= 25000)
q, = readints()
assert(0 <= q <= 1000)
for i in xrange(q) :
    t, = readints()
    assert(0 <= t <= 25000)
exit(42)
