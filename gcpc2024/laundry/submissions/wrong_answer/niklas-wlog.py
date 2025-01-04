#!/bin/python3

k: int = 0


def rem(i: int) -> int:
    # Space remaining to top off the current washing machine
    return k - (i - 1) % k - 1


def wash_fill(a: int, b: int, c: int, abc: int) -> int:
    # Total space remaining to top off all washing machines
    r = rem(a) + rem(b) + rem(c)

    # Calculate the number of washes needed, including the abc washes
    return sum((x - 1) // k + 1 for x in [a, b, c, max(0, abc - r)])


def solve() -> None:
    global k
    k = int(input())
    a, b, c, ab, bc, ac, abc = map(int, input().split())

    res = float("inf")

    # AB all in A
    ac_A1 = max(0, ac - rem(a + ab))
    bc_A1 = max(0, bc - rem(b))
    res = min(
        res,
        (wash_fill(a + ab + (ac - ac_A1), b + (bc - bc_A1), c + ac_A1 + bc_A1, abc)),
    )

    print(res)


for _ in range(int(input())):
    solve()
