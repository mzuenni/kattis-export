#!/usr/bin/env python3

from string import ascii_lowercase as lower

n = int(input())
names = [input() for _ in range(n)]
while len(names)>0:
    most_dutch = min(names, key=lambda s: s.lstrip(lower+" '"))
    names.remove(most_dutch)
    print(most_dutch)

