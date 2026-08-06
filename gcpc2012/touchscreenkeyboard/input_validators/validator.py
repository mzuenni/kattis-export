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
assert(0 < T < 20)
for t in xrange(T) :
    word,l = stdin.readline().split()
    l = int(l)
    assert(len(word) <= 10000)
    assert(search('^[a-z]*$',word))
    assert(0 < l <= 10)
    seen = set()
    for i in xrange(l) :
        s = stdin.readline().rstrip(linesep)
        assert(len(s) == len(word))
        assert(search('^[a-z]*$',s))
        assert(s not in seen)
        seen.add(s)
exit(42)
