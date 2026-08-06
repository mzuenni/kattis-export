#!/usr/bin/env python

from os import linesep
from sys import stdin,exit
from re import search
from datetime import datetime

def readints() :
    return (int(x) for x in stdin.readline().split())

def readlist() :
    array = stdin.readline().split()
    assert (int(array[0])+1==len(array))
    return array[1:]

def checkdate(date, time):
    date = datetime.strptime(date+' '+time, '%Y-%m-%d %H:%M')
    assert(2013 <= date.year <= 2016)

T, = readints()
assert (1 <= T <= 100)
for t in xrange(T):
    B,C = readints()
    assert (1 <= B <= 5000)
    assert (0 <= C <= 360)
    for b in xrange(B):
        id,date1,time1,date2,time2 = stdin.readline().split()
        assert(len(id)<=20)
        checkdate(date1,time1)
        checkdate(date2,time2)

exit(42)
