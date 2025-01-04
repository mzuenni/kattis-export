#!/bin/python3

_ = input()
t = list(map(int, input().split()))


def pred(intercept: int) -> int:
    return sum(abs(v - (intercept + i)) for i, v in enumerate(t))


# Search for the lowest loss and print it.
# Binary Search
lo, hi = -(25 * 10**4), 25 * 10**4
while lo < hi:
    mid = (lo + hi) // 2
    if pred(mid) < pred(mid + 1):
        hi = mid
    else:
        lo = mid + 1

print(pred(lo))
