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

w, = readints()
assert(1 < w < 300000)
for t in xrange(w):
    word = stdin.readline().rstrip()
    assert(1 <= len(word) <= 8)
    assert(search('^[A-Z]*$',word))
blank = stdin.readline().rstrip()
assert(blank=='')
b, = readints()
for t in xrange(b):
    if (t):
        blank = stdin.readline().rstrip()
        assert(blank=='')
    for s in xrange(4):
        word = stdin.readline().rstrip()
        assert(len(word) == 4)
        assert(search('^[A-Z]*$',word))
exit(42)
