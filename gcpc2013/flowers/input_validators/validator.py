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

V,N = stdin.readline().split()
V = float(V)
assert (0 < V <= 1e5)
N = int(N)
assert (0 < N <= 5)
for k in xrange(N):
    a,b,h = readfloats()
    assert(0 <= a <= 10)
    assert(0 <= b <= 10)
    assert(1 <= h <= 10)

exit(42)
