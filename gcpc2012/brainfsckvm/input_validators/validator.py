#!/usr/bin/env python

from os import linesep
from sys import stdin,exit
from re import search

def readints() :
    return (int(x) for x in stdin.readline().split())

T = int(stdin.readline())
assert(0 < T <= 20)
for t in xrange(T) :
    sm,sc,si = readints()
    assert(0 < sm <= 100000)
    assert(0 < sc < 4096)
    assert(0 < si < 4096)
    program = stdin.readline().rstrip(linesep)
    assert(len(program)==sc)
    assert(search('^[-+<>[\].,]*$',program))
    input = stdin.readline().rstrip(linesep)
    assert(len(input)==si)
    assert(not search('\s',input))
exit(42)
