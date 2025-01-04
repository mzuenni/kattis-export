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
    # Wrongfully, all batches are placed in full!
    # This leaves us with 2*2*2*3 = 24 combinations. Try all and find the lowest wash count.

    res = float("inf")
    for ab_a in [0, ab]:
        ab_b = ab - ab_a
        for ac_a in [0, ac]:
            ac_c = ac - ac_a
            for bc_b in [0, bc]:
                bc_c = bc - bc_b

                res = min(
                    res, wash(a + ab_a + ac_a + abc, b + bc_b + ab_b, c + ac_c + bc_c)
                )
                res = min(
                    res, wash(a + ab_a + bc_b, b + bc_c + ab_b + abc, c + ac_a + ac_c)
                )
                res = min(
                    res, wash(a + ab_a + ac_a, b + bc_b + ab_b, c + ac_c + bc_c + abc)
                )

    print(res)


for _ in range(int(input())):
    solve()
