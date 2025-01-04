#!usr/bin/python3
import itertools
from time import sleep

n = int(input())
switch = set()
o_to_e = set()
keep = set()
cur = 0


def give_from_set(ch, cur):
    if ch == 's':
        return switch.pop(), 1 - cur
    if ch == 'e':
        return o_to_e.pop(), 0
    if ch == 'k':
        return keep.pop(), cur


def read_in(val):
    i = input()
    c, x = i.split()
    if c == '+':
        if int(x) % 2 == 0:  # even
            keep.remove(i)
            return val
        else:  # odd
            switch.remove(i)
            return 1 - val
    else:  # c= '*'
        if int(x) % 2 == 0:  # even
            o_to_e.remove(i)
            return 0
        else:  # odd
            keep.remove(i)
            return val


for _ in range(n):
    i = input()
    c, x = i.split()
    if c == '+':
        if int(x) % 2 == 0:  # even
            keep.add(i)
        else:  # odd
            switch.add(i)
    else:  # c= '*'
        if int(x) % 2 == 0:  # even
            o_to_e.add(i)
        else:  # odd
            keep.add(i)

cur = int(input()) % 2

dp = {(s, e, k, p): {"end_even": False, "end_odd": False} for (s, e, k, p) in
      itertools.product(range(len(switch) + 1), range(len(o_to_e) + 1), range(len(keep) + 1), (0,1))}

for s in range(len(switch) + 1):
    for e in range(len(o_to_e) + 1):
        for k in range(len(keep) + 1):
            for p in [0, 1]:
                if (s + e + k) == 0:
                    dp[(s, e, k, p)]["end_odd"] = p % 2 == 1
                    dp[(s, e, k, p)]["end_even"] = p % 2 == 0
                    continue
                if s > 0 and not dp[(s - 1, e, k, 1-p)]["end_odd"]:
                    dp[(s, e, k, p)]["end_even"] = 's'
                if e > 0 and not dp[(s, e - 1, k, 0)]["end_odd"]:
                    dp[(s, e, k, p)]["end_even"] = 'e'
                if k > 0 and not dp[(s, e, k - 1, p)]["end_odd"]:
                    dp[(s, e, k, p)]["end_even"] = 'k'
                if s > 0 and not dp[(s - 1, e, k, 1-p)]["end_even"]:
                    dp[(s, e, k, p)]["end_odd"] = 's'
                if e > 0 and not dp[(s, e - 1, k, 0)]["end_even"]:
                    dp[(s, e, k, p)]["end_odd"] = 'e'
                if k > 0 and not dp[(s, e, k - 1, p)]["end_even"]:
                    dp[(s, e, k, p)]["end_odd"] = 'k'

cur %= 2
goal = "end_odd" if dp[(len(switch), len(o_to_e), len(keep), cur)]["end_odd"] is not False else "end_even"

if goal == "end_odd":
    print("me", flush=True)
    read = False
else:
    print("you", flush=True)
    read = True

while len(switch) + len(o_to_e) + len(keep) > 0:
    if read:
        cur = read_in(cur)
    else:
        out, cur = give_from_set(dp[(len(switch), len(o_to_e), len(keep), cur)][goal], cur)
        print(out, flush=True)
    read ^= 1
