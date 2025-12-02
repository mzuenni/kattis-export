#!/usr/bin/env python3
import sys
import random

random.seed(int(sys.argv[1]))

n_str = sys.argv[2]
if ".." in n_str:
    n = random.randint(*map(int, n_str.split("..")))
else:
    n = int(n_str)

print(n)
print(
    "".join(
        random.choices(
            "rgb",
            weights=tuple(map(int, sys.argv[3:6])) if len(sys.argv) >= 6 else (1, 1, 1),
            k=n,
        )
    )
)
