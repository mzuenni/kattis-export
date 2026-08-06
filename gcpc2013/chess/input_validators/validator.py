#!/usr/bin/env python

from os import linesep
from sys import stdin,exit
from re import search
from datetime import datetime

def readints() :
    return (int(x) for x in stdin.readline().split())

T, = readints()
for t in xrange(T):
    a,b,c,d = stdin.readline().split()
    assert(a in 'ABCDEFGH')
    assert(1 <= int(b) <= 8)
    assert(c in 'ABCDEFGH')
    assert(1 <= int(d) <= 8)

exit(42)
