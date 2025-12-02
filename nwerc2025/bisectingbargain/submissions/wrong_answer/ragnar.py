#!/usr/bin/env python3

n = int(input())

coins = [1, 2, 5, 10, 20, 50, 100, 200, 500]


def greedy(n, depth=0):
    # print('greedy', n, depth)
    ans = []
    for c in reversed(coins):
        if c * 10**depth > 500:
            continue
        while n >= c:
            n -= c
            ans.append(c)
    return ans


def solve(n, depth=0):
    # print('solve', n, depth)

    if depth == 3:
        return greedy(n, depth - 1)

    if n == 0:
        return None
    if n % 2 == 1:
        return greedy(n, depth)

    def recurse(take):
        x = n - sum(take)
        assert x % 10 == 0
        s = solve(x // 10, depth + 1)
        if s is None:
            return None
        return [10 * x for x in s] + take

    d = n % 10
    if d == 0:
        return recurse([])
    if d == 2:
        return greedy(n - 2) + [2]
    if d == 6:
        return greedy(n - 6) + [5, 1]
    if d == 8:
        return greedy(n - 8) + [5, 1, 1, 1]
    if n % 20 == 14:
        return greedy(n - 4) + [2, 2]

    if n % 20 == 4:
        return recurse([2, 2])

    print(n)
    assert False


ans = solve(n)
if ans is None:
    print("splittable")
else:
    # print("unsplittable")
    print(len(ans))
    print(*ans)
