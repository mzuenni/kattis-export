#!/bin/python3

k: int = 0


def solve() -> None:
    global k
    k = int(input())
    a, b, c, ab, bc, ac, abc = map(int, input().split())

    print(int(sum([a, b, c, ab, bc, ac, abc]) // k + 1))


for _ in range(int(input())):
    solve()
