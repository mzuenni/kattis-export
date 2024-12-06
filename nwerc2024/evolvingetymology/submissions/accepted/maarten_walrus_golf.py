#!/usr/bin/env python3

(k := int(input().split()[1])), (n := len(s := input())), print("".join(s[i * pow(2, k, n) % n] for i in range(n)))
