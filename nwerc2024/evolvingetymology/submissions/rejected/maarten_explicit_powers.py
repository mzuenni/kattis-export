#!/usr/bin/env python3
# @EXPECTED_RESULTS@: RUN_TIME_ERROR, TIME_LIMIT_EXCEEDED
# It's either too slow, or uses too much memory to calculate `2 ** k`.

(n, k), s = map(int, input().split()), input()
print("".join(s[i * 2 ** k % n] for i in range(n)))
