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

    # AB all in B
    ac_B1 = max(0, ac - rem(a))
    bc_B1 = max(0, bc - rem(b + ab))
    res = min(
        res, wash_fill(a + (ac - ac_B1), b + ab + (bc - bc_B1), c + ac_B1 + bc_B1, abc)
    )

    # AC all in A
    ab_A2 = max(0, ab - rem(a + ac))
    bc_A2 = max(0, bc - rem(c))
    res = min(
        res, wash_fill(a + ac + (ab - ab_A2), b + ab_A2 + bc_A2, c + (bc - bc_A2), abc)
    )

    # AC all in C
    ab_C1 = max(0, ab - rem(a))
    bc_C1 = max(0, bc - rem(c + ac))
    res = min(
        res, wash_fill(a + (ab - ab_C1), b + ab_C1 + bc_C1, c + ac + (bc - bc_C1), abc)
    )

    # BC all in B
    ab_B2 = max(0, ab - rem(b + bc))
    ac_B2 = max(0, ac - rem(c))
    res = min(
        res, wash_fill(a + ab_B2 + ac_B2, b + bc + (ab - ab_B2), c + (ac - ac_B2), abc)
    )

    # BC all in C
    ab_C2 = max(0, ab - rem(b))
    ac_C2 = max(0, ac - rem(c + bc))
    res = min(
        res, wash_fill(a + ab_C2 + ac_C2, b + (ab - ab_C2), c + bc + (ac - ac_C2), abc)
    )

    print(res)


for _ in range(int(input())):
    solve()
