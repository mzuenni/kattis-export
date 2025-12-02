#!/usr/bin/env python3
import random

n = int(input())
a = list(map(int, input().split()))

ans = []

def move(x, y):
    ans.append((x+1, y+1))
    out = a[x:x+3]
    del a[x:x+3]
    a[y:y] = out
    # print('after  move', a)

for i in range(n-1, 2, -1):
    idx = a.index(i+1)
    # print(i+1, 'is at', idx)
    if idx == 0:
        move(0, 1)
        idx = 1
    if idx == 1:
        move(0, 1)
        idx = 2
    assert idx >= 2
    move(idx-2, i-2)

# Random moves until success
while a[0:5] != [1, 2, 3, 4, 5]:
    x = random.randint(0, 2)
    y = random.randint(0, 2)
    move(x, y)

# At this point all but the first 5 positions are good
print(len(ans))
for x, y in ans:
    print(x, y)
# print(a)
