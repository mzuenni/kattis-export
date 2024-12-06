#!/usr/bin/env python3

n = int(input())
names = [input() for _ in range(n)]


def key(name):
    pos = 0
    while not (ord("A") <= ord(name[pos]) <= ord("Z")):
        pos += 1
    return name[pos:]


names.sort(key=key)
print(*names, sep="\n")
