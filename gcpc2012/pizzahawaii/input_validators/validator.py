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
assert(0 < T <= 20)
for t in xrange(T) :
    n, = readints()
    assert(1 <= n <= 60)
    for i in xrange(n) :
        pizza = stdin.readline().rstrip(linesep)
        assert(3 <= len(pizza) <= 20)
        assert(search('^[A-Za-z]*$',pizza))
        for j in xrange(2) :
            ingredients = readlist()
            assert (1 <= len(ingredients) <= 20)
            for item in ingredients: assert (2 <= len(item) <= 20)
exit(42)
