#!/usr/bin/env python3
import sys, random

random.seed(int(sys.argv[1]))

prefix = int(sys.argv[2])
noise = int(sys.argv[3])

cases = []

for h in range(3, 9):
    for w in range(3, 9):
        if h * w == 9:
            # smaller covered by complete cases
            continue
        for k in range(1, h * w - 1):
            cs = list("#" * k + "." * (h * w - k))
            if noise:
                a = random.randint(0, k - 1)
                b = random.randint(k, h * w - 1)
                cs[a], cs[b] = cs[b], cs[a]
                if k > 1 and h * w - k > 1 and noise == 2:
                    a2, b2 = a, b
                    while a2 == a:
                        a2 = random.randint(0, k - 1)
                    while b2 == b:
                        b2 = random.randint(k, h * w - 1)
                    cs[a2], cs[b2] = cs[b2], cs[a2]
            if prefix:
                cs = cs[::-1]
            cs = [cs[i:i + w] for i in range(0, len(cs), w)]
            cases.append(cs)

random.shuffle(cases)
assert len(cases) <= 10000
print(len(cases))
for cs in cases:
    print(len(cs), len(cs[0]), sum(l.count('#') for l in cs))
    for line in cs:
        print(''.join(line))

