#!/usr/bin/env python3
from collections import Counter
from math import comb

n, counts = int(input()), sorted(Counter(input()).values())
if len(counts) == 1:
    print(0)
elif len(counts) == 2:
    # Strategy: change the coloured light with the fewest occurrences to the other one (takes expected 3 steps each).
    print(3 * counts[0])
else:
    a, b, c = counts
    # Strategy:
    print(
        # Change the coloured light with the fewest occurrences to one of the other two (takes expected `1.5 * a` steps).
        1.5 * a +
        # There are `2 ** a` possible ways in which these first lights turned into the other two colours of lights.
        sum(
            # But only the number of lights in each colour is relevant, so we combine them (pun on "combinations" intended).
            # Say that `i` lights turned into colour `b`, this happens `comb(a, i)` times.
            comb(a, i) * (
                # Change the minimum of the two remaining colours `(b + i, c + (a - i))` to the final colour (takes expected 3 steps each).
                3 * min(b + i, c + (a - i))
            )
            for i in range(a + 1)
        ) / 2 ** a
    )
