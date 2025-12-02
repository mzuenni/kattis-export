#!/usr/bin/env python3

if input() == "send":
    n, s = int(input()), input()
    print("\n".join(f"{i:03b}" + "".join(f"{ord(s[j]) - 96:05b}"[i] for j in range(n)) for i in range(5)))
else:
    ss = sorted(input() for _ in range(5))
    print("".join(chr(int("".join(ss[i][j] for i in range(5)), 2) + 96) for j in range(3, len(ss[0]))))
