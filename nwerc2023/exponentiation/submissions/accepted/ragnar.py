#!/usr/bin/env python3
n, m = map(int, input().split())
order1 = list(range(n))
order2 = list(reversed(range(n)))

mapping = list(range(n))
children = [[] for _ in range(n)]

remap = {-1: "<", 1: ">", 0: "="}

def cmp(i, j):
    if i == j:
        return 0
    assert i != j
    c1 = order1.index(i) < order1.index(j)
    c2 = order2.index(i) < order2.index(j)
    if c1 != c2:
        return 0
    if c1:
        return -1
    else:
        return 1


def cmp_children(i, j):
    for k in range(min(len(children[i]), len(children[j]))):
        c = cmp(children[i][k], children[j][k])
        if c != 0:
            return c
    if len(children[i]) > len(children[j]):
        return 1
    elif len(children[i]) < len(children[j]):
        return -1
    else:
        return 0


for _ in range(m):
    op, i, j = input().split()
    i, j = int(i) - 1, int(j) - 1
    if op == "!":
        new_i = n
        n += 1
        old_i = mapping[i]
        mapping[i] = new_i
        children.append(children[old_i].copy())
        children[new_i].append(mapping[j])
        children[new_i].sort(key=lambda x: order1.index(x), reverse=True)
        order1.append(new_i)
        idx = order1.index(new_i)
        while cmp_children(order1[idx], order1[idx - 1]) < 0:
            order1[idx], order1[idx - 1] = order1[idx - 1], order1[idx]
            idx -= 1
        order2.append(new_i)
        idx = order2.index(new_i)
        while cmp_children(order2[idx], order2[idx - 1]) <= 0:
            order2[idx], order2[idx - 1] = order2[idx - 1], order2[idx]
            idx -= 1
    else:
        i = mapping[i]
        j = mapping[j]
        if i == j:
            print(remap[0])
        else:
            print(remap[cmp(i, j)])
