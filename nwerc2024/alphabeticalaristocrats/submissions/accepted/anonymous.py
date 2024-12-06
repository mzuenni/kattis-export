#!/usr/bin/env python3
print("\n".join(sorted(map(input, [""] * int(input())), key=lambda s: s[next(i for i, c in enumerate(s) if c.isupper()):])))
