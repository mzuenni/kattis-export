#!/usr/bin/env python

from os import linesep
from sys import stdin,exit
from re import search

def readints() :
    return (int(x) for x in stdin.readline().split())

T = int(stdin.readline())
assert(0 < T < 100)
for t in xrange(T) :
    k,c = readints()
    assert(1 <= k <= 1e9)
    assert(1 <= c <= 1e9)
exit(42)
