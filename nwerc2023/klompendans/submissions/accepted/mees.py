#!/usr/bin/python3

n = int(input())
a, b = [int(x) for x in input().split()]
c, d = [int(x) for x in input().split()]
s = [(0, 0, 0), (0, 0, 1)]
seen = set([(0, 0, 0), (0, 0, 1)])

def nbs(x, y, a, b):
    return [(nx, ny) for (nx, ny) in [(x + a, y + b),
                                      (x + a, y - b),
                                      (x - a, y + b),
                                      (x - a, y - b),
                                      (x + b, y + a),
                                      (x + b, y - a),
                                      (x - b, y + a),
                                      (x - b, y - a)] if 0 <= nx < n and 0 <= ny < n]

while len(s) != 0:
    x, y, m = s[-1]
    s.pop()
    if m == 0:
        for nx, ny in nbs(x, y, a, b):
            if (nx, ny, 1 - m) not in seen:
                seen.add((nx, ny, 1-m))
                s.append((nx, ny, 1-m))
    else:
        for nx, ny in nbs(x, y, c, d):
            if (nx, ny, 1 - m) not in seen:
                seen.add((nx, ny, 1-m))
                s.append((nx, ny, 1-m))

print(len(set([(x, y) for x, y, m in seen])))
