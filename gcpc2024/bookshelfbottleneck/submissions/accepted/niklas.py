#!/bin/python3
i = [tuple(map(int, x.split())) for x in open(0).readlines()]
print("impossible" if any(min(t) > i[0][1] for t in i[1:]) else sum(sorted(t)[sorted(t)[1] > i[0][1]] for t in i[1:]))
