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
assert (1 <= T <= 100)
for t in xrange(T):
    if t:
        blank = stdin.readline().rstrip()
        assert(blank=='')
    assert(search('^###[o.]{3}###$',stdin.readline().rstrip()))
    assert(search('^[o.]{9}$',stdin.readline().rstrip()))
    assert(search('^[o.]{9}$',stdin.readline().rstrip()))
    assert(search('^[o.]{9}$',stdin.readline().rstrip()))
    assert(search('^###[o.]{3}###$',stdin.readline().rstrip()))

exit(42)
