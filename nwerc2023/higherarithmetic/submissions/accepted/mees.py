#!/usr/bin/python3

import sys

n = int(input())
a = [int(x) for x in input().split()]
num_ones = len([x for x in a if x == 1])
num_twos = len([x for x in a if x == 2])
if num_ones == 1 and num_twos == 0:
    a = [x for x in a if x != 1]
    if a == []:
        print(1)
    else:
        a.sort()
        print(f"(1+{a[0]})", *a[1:], sep="*")
    sys.exit()

a = [str(x) for x in a if x != 1 and x != 2]

if num_twos >= num_ones:
    a.extend(["(1+2)"]*(num_ones))
    a.extend(["2"]*(num_twos-num_ones))
    num_ones = 0
elif num_ones > num_twos + 1:
    a.extend(["(1+2)"]*num_twos)
    num_ones -= num_twos
    while num_ones > 4:
        a.append("(1+1+1)")
        num_ones -= 3
    a.append("(" + "+".join("1" for _ in range(num_ones)) + ")")
elif num_ones == num_twos + 1:
    a.extend(["(1+2)"]*(num_twos - 1))
    a.append("2")
    a.append("(1+1)")

print(*a, sep="*", end="")
