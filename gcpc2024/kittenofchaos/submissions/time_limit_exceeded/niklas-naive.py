#!/bin/python3

s: list[str] = list(input())
t: str = input()
x = "bdpq"

for c in t:
    if c == 'h':
        s = ["dbqp"[x.index(c)] for c in reversed(s)]
    elif c == 'v':
        s = ["pqbd"[x.index(c)] for c in s]
    elif c == 'r':
        s = ["qpdb"[x.index(c)] for c in reversed(s)]


print("".join(s))
