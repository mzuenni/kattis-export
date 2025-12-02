#!/usr/bin/env python3
import sys, random

random.seed(int(sys.argv[1]))

h = int(sys.argv[2])
w = int(sys.argv[3])

case_set = set()
case_list = []

for a in range(h * w):
    for b in range(a + 1, h * w + 1):
        if a + b == h * w:
            continue
        cur = "." * a + "#" * (b - a) + "." * (h * w - b)
        case_set.add(cur)
        case_list.append(cur)

while len(case_list) < 10000:
    cur = random.choice(case_list)
    a = random.randint(0, len(cur) - 1)
    b = random.randint(0, len(cur) - 1)
    if cur[a] == cur[b]:
        continue
    cur = list(cur)
    cur[a], cur[b] = cur[b], cur[a]
    cur = "".join(cur)
    if cur in case_set:
        continue
    case_set.add(cur)
    case_list.append(cur)

random.shuffle(case_list)
print(len(case_list))
for cs in case_list:
    cs = [cs[i:i + w] for i in range(0, len(cs), w)]
    print(len(cs), len(cs[0]), sum(l.count('#') for l in cs))
    for line in cs:
        print(''.join(line))

