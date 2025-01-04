#!/bin/python3

k: int = 0


def wash(a: int, b: int, c: int) -> int:
    # Calculate the number of washes needed, including the abc washes
    return sum((x - 1) // k + 1 for x in [a, b, c])


def solve() -> None:
    global k
    k = int(input())
    a, b, c, ab, bc, ac, abc = map(int, input().split())

    # Bruteforce all possible combinations of washing.
    # AB can go into a or b, AC can go into a or c, BC can go into b or c.
    # ABC can go into any of the three.
    # Try all and find the lowest wash count.

    res = float("inf")
    for ab_a in range(ab + 1):
        ab_b = ab - ab_a
        for ac_a in range(ac + 1):
            ac_c = ac - ac_a
            for bc_b in range(bc + 1):
                bc_c = bc - bc_b
                for a_abc in range(abc + 1):
                    for b_abc in range(abc + 1 - a_abc):
                        c_abc = abc - a_abc - b_abc

                        res = min(
                            res,
                            wash(
                                a + ab_a + ac_a + a_abc,
                                b + bc_b + ab_b + b_abc,
                                c + ac_c + bc_c + c_abc,
                            ),
                        )

    print(res)


for _ in range(int(input())):
    solve()
