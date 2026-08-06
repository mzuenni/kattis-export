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
assert(0 < T <= 160000)
for t in xrange(T) :
    j,p,H,L = readints()
    assert(0 < j <= 500)
    assert(0 < p <= 500)
    assert(0 < H <= 500)
    assert(0 < L <= 500)
exit(42)
