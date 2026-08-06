#!/usr/bin/env python

from os import linesep
from sys import stdin,exit
from re import search

def readints() :
    return (int(x) for x in stdin.readline().split())

T = int(stdin.readline())
assert(0 < T <= 100)
for t in xrange(T) :
    M1,N1,K1,M2,N2,K2 = readints()
    assert(1 <= M1 <= 1e5)
    assert(1 <= N1 <= 250)
    assert(1 <= K1 <= 250)
    for i in xrange(M1) :
        Tin, Tout, S = readints()
        assert(0 <= Tin < N1)
        assert(0 <= Tout < N1)
        assert(0 <= S < K1)
    for i in xrange(M2) :
        Tin, Tout, S = readints()
        assert(0 <= Tin < N2)
        assert(0 <= Tout < N2)
        assert(0 <= S < K2)
exit(42)
