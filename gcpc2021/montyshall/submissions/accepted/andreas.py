#!/usr/bin/env python3
d, s, e = map(float, input().split())
always_select = max(0.0, 2*s + e - d)

p_def = always_select / d

d -= always_select
s -= always_select

p_first = s / d
p_second = s / (d - s - e)

print("%.20f" % (p_def + (1.0 - p_def) * (1.0 - p_first) * p_second))
