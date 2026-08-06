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

R,C = readints()
assert (3 <= R <= 300)
assert (3 <= C <= 300)
for i in xrange(R):
    cc = list(readints())
    assert (len(cc)==C)
    for c in cc:
        assert (0 <= c <= 100000)

r,c = readints()
assert (0 < r < R-1)
assert (0 < c < C-1)

exit(42)
