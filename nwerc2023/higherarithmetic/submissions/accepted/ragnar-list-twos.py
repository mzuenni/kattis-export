#!/usr/bin/env python3
n = int(input())
a = sorted(list(map(lambda x: (int(x), int(x)), input().split())), reverse=True)
ones = 0
while len(a) > 0 and a[-1][0] == 1:
    ones += 1
    a.pop()
twos = 0
while len(a) > 0 and a[-1][0] == 2:
    twos += 1
    a.pop()
for _ in range(min(ones, twos)):
    a.append((3, 2))
    ones -= 1
    twos -= 1
for _ in range(twos):
    a.append((2, 2))
for _ in range(ones):
    if len(a) > 0 and a[-1][0] < 3:
        x, x0 = a.pop()
        a.append((x + 1, x0))
    else:
        a.append((1, 1))
if len(a) > 1 and a[-1][0] == 1:
    a.pop()
    x, x0 = a.pop()
    a.append((x + 1, x0))


def term(x, x0):
    return "(" + "+".join([str(x0)] + ["1"] * (x - x0)) + ")"


print("*".join(term(x, x0) for x, x0 in a))
