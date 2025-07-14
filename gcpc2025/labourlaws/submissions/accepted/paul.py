#!/usr/bin/env python3

def min_break(work):
  if work > 600:
    return 123456789
  if work > 540:
    return 45
  if work > 360:
    return 30
  return 0

here = int(input())
for work in range(here, -1, -1):
  if min_break(work) <= here-work:
    print(here-work)
    break # pun intended!
