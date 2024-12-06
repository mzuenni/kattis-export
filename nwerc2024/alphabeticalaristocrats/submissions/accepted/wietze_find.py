#!/usr/bin/env python3

a = [input() for _ in range(int(input()))]
a.sort(key = lambda s: s[min([s.find(chr(x))%99 for x in range(65,91)]):])
print(*a,sep='\n')
