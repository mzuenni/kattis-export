#!/usr/bin/env python3

mode = input().strip()
n = int(input())
s = input().strip()
if mode == "Encode":
    if s.count(s[0]) == len(s):
        print(s)
    else:
        c_count = s.find("01"[s[0] == "0"])
        print("2" * c_count + s[c_count:])
else:
    if "2" not in s:
        print(s)
    else:
        start = next(
            i for i in range(len(s)) if s[i] == "2" and s[(i - 1) % len(s)] != "2"
        )
        s = s[start:] + s[:start]  # unrotate
        c_count = s.rfind("2") + 1
        original_char = "01"[s[c_count] == "0"]
        print(original_char * c_count + s[c_count:])
