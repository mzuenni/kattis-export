#!/usr/bin/env python

from os import linesep
from sys import stdin,exit
from re import search
from math import log10

def readints() :
    return (int(x) for x in stdin.readline().split())

def readfloats() :
    return (float(x) for x in stdin.readline().split())

def readlist() :
    array = stdin.readline().split()
    assert (int(array[0])+1==len(array))
    return array[1:]

C, = readints()
assert (1 <= C <= 5000)
for i in xrange(C):
    M,Z,r = readints()
    assert(0 < M <=1e18)
    assert(0 <= Z <= M-1)
    assert(r >= 1)
    assert(r <= log10(M)+1)
    
exit(42)
