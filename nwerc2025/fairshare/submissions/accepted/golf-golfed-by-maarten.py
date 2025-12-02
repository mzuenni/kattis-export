#!/usr/bin/env python3

D = sum(x := [eval(input().replace(" ", "-")) for _ in [0] * int(input())])
print([f"{(x := [d - (D < d) * 9e9 for d in x]).index(m := max(x)) + 1}", "impossible"][D - m > 4e9])
