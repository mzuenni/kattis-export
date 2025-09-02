'''
Created on 18.05.2017

@author: Moritz Fuchs
'''
from collections import defaultdict

def find(start, end):
    seen=set()
    q = [x[0]]
    while q:
        c = q.pop(0)
        for n in out[c]:
            if n == x[1]:
                return True
            elif n not in seen:
                q.append(n)
                seen.add(n)
    return False

n,m = map(int,raw_input().split())

inc = defaultdict(lambda:list())
out = defaultdict(lambda:list())

for _ in range(n):
    s = raw_input()
    if " are worse than " in s:
        x = s.split(" are worse than ")
        out[x[0]].append(x[1])
        inc[x[1]].append(x[0])
    else:
        worst = s.split()[0]

for _ in range(m):
    s = raw_input()
    if " are worse than " in s:
        x = s.split(" are worse than ")
        if find(*x):
            print("Fact")
        elif find(*x[::-1]):
            print("Alternative Fact")
        else:
            print("Pants on Fire")
    else:
        w = s.split()[0]
        if w == worst:
            print("Fact")
        elif len(inc[w]) > 0:
            print("Alternative Fact")
        else:
            print("Pants on Fire")