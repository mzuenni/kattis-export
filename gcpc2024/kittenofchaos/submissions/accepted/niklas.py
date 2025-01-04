#!/bin/python3

s: list[str] = list(input())
t: str = input()
x = "bdpq"

p = len(t)
while p > 0 and t:
    t = (
        t.replace("hv", "r")
        .replace("vh", "r")
        .replace("hr", "v")
        .replace("rh", "v")
        .replace("vr", "h")
        .replace("rv", "h")
        .replace("rr", "")
        .replace("hh", "")
        .replace("vv", "")
    )
    p -= len(t)

for c in t:
    if c == 'h':
        s = ["dbqp"[x.index(c)] for c in reversed(s)]
    elif c == 'v':
        s = ["pqbd"[x.index(c)] for c in s]
    elif c == 'r':
        s = ["qpdb"[x.index(c)] for c in reversed(s)]


print("".join(s))
