#!/usr/bin/env python3
# @EXPECTED_RESULTS@: ACCEPTED, TIME_LIMIT_EXCEEDED
n = int(input())
a = sorted(list(map(lambda x: (int(x), int(x)), input().split())), reverse=True)
ones = 0
while len(a) > 0 and a[-1][0] == 1:
    ones += 1
    a.pop()
twos = a.count((2, 2))
large = len(a) - twos
for _ in range(ones):
    if len(a) > 0 and a[-1][0] < 3:
        x, x0 = a.pop()
        if x + 1 == 3:
            a.insert(large, (x + 1, x0))
            large += 1
        else:
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
