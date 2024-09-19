#!/usr/bin/env python3
# @EXPECTED_RESULTS@: WRONG_ANSWER,TIME_LIMIT_EXCEEDED
import sys
import random

# Stores all loglogs and compares. Uses 3 instead of 2023.

n,m = map(int,input().split())
nums = [0] * n

for _ in range(m):
    ch,i,j = input().split()
    i = int(i)-1
    j = int(j)-1
    if ch == '?':
        if nums[i] < nums[j]:
            print("<")
        elif nums[i] > nums[j]:
            print(">")
        else:
            print("=")
    else:
        nums[i] += 3**nums[j]

