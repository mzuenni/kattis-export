#!/usr/bin/env python3
import sys

h, w = map(int, input().split())
for _ in range(h):
    row = input()
    if len(row) != w:
        sys.exit(43)

sys.exit(42)
