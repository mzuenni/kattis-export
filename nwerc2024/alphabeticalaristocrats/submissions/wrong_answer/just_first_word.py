#!/usr/bin/env python3

from string import ascii_lowercase as lower

n = int(input())
names = [input() for _ in range(n)]
names.sort(key=lambda s: s.lstrip(lower+" '").split()[0])
print(*names, sep='\n')
