'''
Created on 18.05.2017

@author: Moritz Fuchs
'''
from collections import defaultdict

def find(start, end):
    seen=set()
    q = [start]
    while q:
        c = q.pop(0)
        for n in out[c]:
            if n == end:
                return True
            elif n not in seen:
                q.append(n)
                seen.add(n)
    return False

n,m = list(map(int,input().split()))
out = defaultdict(lambda:list())

for _ in range(n):
    s = input()
    x = s.split(" are worse than ")
    out[x[0]].append(x[1])

for _ in range(m):
    s = input()
    x = s.split(" are worse than ")
    if find(*x):
        print("Fact")
    elif find(*x[::-1]):
        print("Alternative Fact")
    else:
        print("Pants on Fire")
