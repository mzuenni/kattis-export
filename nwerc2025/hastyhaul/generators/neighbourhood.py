#!/usr/bin/env python3
import sys, random

random.seed(int(sys.argv[1]))

h = int(sys.argv[2])
w = int(sys.argv[3])
k = int(sys.argv[4])
d = int(sys.argv[5])

cases = []

found = set()
next_layer = []
start = list("#" * k + "." * (h * w - k))
random.shuffle(start)
found.add("".join(start))
next_layer.append(start)

for _ in range(d):
    cur_layer = next_layer
    next_layer = []
    for cur in cur_layer:
        for a in range(h * w):
            for b in range(a + 1, h * w):
                if cur[a] == cur[b]:
                    continue
                cp = cur[:]
                cp[a], cp[b] = cp[b], cp[a]
                scp = "".join(cp)
                if scp in found:
                    continue
                found.add(scp)
                assert len(found) <= 10000
                next_layer.append(cp)

found = list(found)
random.shuffle(found)
assert len(found) <= 10000
print(len(found))
for cs in found:
    cs = [cs[i:i + w] for i in range(0, len(cs), w)]
    print(h, w, sum(l.count('#') for l in cs))
    for line in cs:
        print(''.join(line))

