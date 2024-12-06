#!/usr/bin/env python3

def findCapital(s):
    for idx, char in enumerate(s):
        if char in "ABCDEFGHIJKLMNOPQRSTUVWXYZ": return idx

a = [input() for _ in range(int(input()))]
a.sort(key = lambda s: s[findCapital(s):])
print(*a,sep='\n')

