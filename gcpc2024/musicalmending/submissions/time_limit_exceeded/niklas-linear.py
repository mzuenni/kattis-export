#!/bin/python3

_ = input()
t = list(map(int, input().split()))


def pred(intercept: int) -> int:
    return sum(abs(v - (intercept + i)) for i, v in enumerate(t))


# Search for the lowest loss and print it.
# Linear Search
print(min(pred(i) for i in range(-25 * 10**4, 25 * 10**4)))
